#include "GetData.h"
#include "JsonParser.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
/**
 *User interface reference
 *
 */
#define UI_FILE "ViewWidget.glade"

/**
 *
 * Declaring builder that connects glade's UI with source code
 *
 */
GtkBuilder *builder;

/**
 *
 * Declaring main window
 *
 */
GtkWidget *TopWindow;

/**
 *
 * Declaring button *get info*
 *
 */
GtkButton *track_on;

/**
 *
 * Declaring input widget for video id
 *
 */
GtkEntry *video_id;

/**
 *
 * Declaring output widget
 *
 */
GtkTreeView *stat_info;

/**
 *
 * Enumeration for comfortable and
 *      understandable editing model in :c:func:`create_and_fill_model`
 *
 */
    enum colunms
    {
      /**
       *
       * Name of the raw
       *
       */
      COL_NAME = 0,
      /**
       *
       * Value
       *
       */
      COL_VAL,
      /**
       *
       * Number of the colunms
       *
       */
      NUM_COLS
    };

/**
 *
 * Button handler
 *
 * :param *gobj: Button object
 *
 * After pressing button starts the main functionality of programm
 *  **Firstly it takes video id from `video_id` and
 * send it through :c:func:`GetFromApi`
 * After creating ``temp.json`` it takes all statistics data from file using
 * :c:func:`GetFromJSON_statistics`
 *
 * All results apears in ``stat_info`` widget
 *
 */
void button_on_clicked(GObject *gobj);

/**
 *
 * Common window destroyer
 * :param *object: TopWindow object
 *
 */
void TopWindow_destroy_cb(GObject *object, gpointer user_data);

/**
 *
 * Creating a model for output widget
 *
 * :param views: Number of views
 *
 * :param likes: Number of likes
 *
 * :param dislikes: Number of dislikes
 *
 * :param comments: Number of comments
 *
 * :return: Returns data model for GtkTreeView
 *
 */
static GtkTreeModel *create_and_fill_model(int views, int likes, int dislikes, int comments)
{
    GtkTreeIter iter;
    GtkListStore *info_model;
    //creating model with two columns
    info_model = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_INT);
    // creating views raw
    gtk_list_store_append(info_model, &iter);
    gtk_list_store_set(info_model, &iter,
                       COL_NAME, "views",
                       COL_VAL, views,
                       -1);
    // creating likes raw
    gtk_list_store_append(info_model, &iter);
    gtk_list_store_set(info_model, &iter,
                       COL_NAME, "likes",
                       COL_VAL, likes,
                       -1);
    // creating dislikes raw
    gtk_list_store_append(info_model, &iter);
    gtk_list_store_set(info_model, &iter,
                       COL_NAME, "dislikes",
                       COL_VAL, dislikes,
                       -1);
    // creating comments raw
    gtk_list_store_append(info_model, &iter);
    gtk_list_store_set(info_model, &iter,
                       COL_NAME, "comments",
                       COL_VAL, comments,
                       -1);
    return GTK_TREE_MODEL(info_model);

}

int main(int argc, char** argv)
{

    GError *error = NULL;
    // Initializing gtk
    gtk_init(&argc, &argv);
    // Initializing builder
    builder = gtk_builder_new();

    // Connecting with .glade
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
          g_warning( "%s", error->message);
          g_free( error );
          return( 1 );
    }
    // Connecting each object with his UI realization
    TopWindow = GTK_WIDGET(gtk_builder_get_object(builder, "TopWindow"));
    track_on = GTK_BUTTON(gtk_builder_get_object(builder, "track_on"));
    stat_info = GTK_TREE_VIEW(gtk_builder_get_object(builder, "stat_info"));
    video_id = GTK_ENTRY(gtk_builder_get_object(builder,"video_id"));
    // connect handlers with signals
    gtk_builder_connect_signals(builder, NULL);

    // Creating TextTreeView data structure:
    GtkCellRenderer *renderer;
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(stat_info),
                                                -1,
                                                "info",
                                                renderer,
                                                "text", COL_NAME,
                                                NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(stat_info),
                                                -1,
                                                "count",
                                                renderer,
                                                "text", COL_VAL,
                                                NULL);
    // Filling with empty values to create widget after opening
    gtk_tree_view_set_model(GTK_TREE_VIEW(stat_info), create_and_fill_model(0,0,0,0));

    // Deallocating
    g_object_unref(G_OBJECT(builder));

    // Show all
    gtk_widget_show(TopWindow);

    gtk_main();

    return 0;
}

void TopWindow_destroy_cb(GObject *object, gpointer user_data)
{
    // Exit programm
    gtk_main_quit();
}

void button_on_clicked(GObject *gobj)
{
    int check_get_data;
    // Takes video id to buffer
    const gchar *buffer = gtk_entry_get_text(video_id);
    //printf("id: %s\n", buffer);

    // Making request
    check_get_data = GetFromApi(buffer);
    // Checking request
    if (check_get_data != 0) {
        fprintf(stderr,"Getting data error, errcode: %d \n",check_get_data);
    } else {
        // Parsing earned data
        int count[4];
        for(int i = 0; i < 4; i++){
            count[i] = GetFromJSON_statistics(i);
        }
        // Setting output
        gtk_tree_view_set_model(GTK_TREE_VIEW(stat_info),
                                create_and_fill_model(count[0],
                                                      count[1],
                                                      count[2],
                                                      count[3]));
    }
}
