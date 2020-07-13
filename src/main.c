#include "GetData.h"
#include "JsonParser.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#define UI_FILE "ViewWidget.glade"
GtkBuilder *builder;
GtkWidget *TopWindow;
GtkButton *track_on;
GtkEntry *video_id;
GtkTreeView *stat_info;
    enum
    {
      COL_NAME = 0,
      COL_VAL,
      NUM_COLS
    };

void button_on_clicked(GObject *gobj);
void TopWindow_destroy_cb(GObject *object, gpointer user_data);

static GtkTreeModel *create_and_fill_model(int views, int likes, int dislikes, int comments){
  GtkTreeIter iter;
  GtkListStore *info_model;

  info_model = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_INT);

  gtk_list_store_append(info_model, &iter);
  gtk_list_store_set(info_model, &iter,
                     COL_NAME, "views",
                     COL_VAL, views,
                     -1);
  gtk_list_store_append(info_model, &iter);
  gtk_list_store_set(info_model, &iter,
                     COL_NAME, "likes",
                     COL_VAL, likes,
                     -1);
  gtk_list_store_append(info_model, &iter);
  gtk_list_store_set(info_model, &iter,
                     COL_NAME, "dislikes",
                     COL_VAL, dislikes,
                     -1);
  gtk_list_store_append(info_model, &iter);
  gtk_list_store_set(info_model, &iter,
                     COL_NAME, "comments",
                     COL_VAL, comments,
                     -1);
  return GTK_TREE_MODEL(info_model);

}

int main(int argc, char** argv){

    GError *error = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    if( ! gtk_builder_add_from_file( builder, UI_FILE, &error ) )
      {
          g_warning( "%s", error->message);
          g_free( error );
          return( 1 );
      }
    TopWindow = GTK_WIDGET(gtk_builder_get_object(builder, "TopWindow"));
    track_on = GTK_BUTTON(gtk_builder_get_object(builder, "track_on"));
    stat_info = GTK_TREE_VIEW(gtk_builder_get_object(builder, "stat_info"));
    video_id = GTK_ENTRY(gtk_builder_get_object(builder,"video_id"));
    gtk_builder_connect_signals(builder, NULL);
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
    gtk_tree_view_set_model(GTK_TREE_VIEW(stat_info), create_and_fill_model(0,0,0,0));


    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(TopWindow);

    gtk_main();

    return 0;
}

void TopWindow_destroy_cb(GObject *object, gpointer user_data){
  gtk_main_quit();
}

void button_on_clicked(GObject *gobj){
  const gchar *buffer = gtk_entry_get_text(video_id);
  printf("id: %s\n", buffer);
  GetFromApi(buffer);
  int count[4];
  for(int i = 0; i < 4; i++){
    count[i] = GetFromJSON_statistics(i);
  }
  gtk_tree_view_set_model(GTK_TREE_VIEW(stat_info),
                          create_and_fill_model(count[0], count[1], count[2], count[3]));

}
