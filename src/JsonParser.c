
#include <stdio.h>
#include <json-c/json.h>
#include "JsonParser.h"
#include <string.h>


int GetFromJSON_statistics(int target)
{
    // Opening temp.json file for reading
    FILE* json = fopen("temp.json", "r");

    // Creating budder for execute and work with json structure out of file
    char buffer[2048];

    // Reading from file to buffer
    fread(buffer, 2048, 1, json);

    // Initializating storage json objects
    json_object *parsed_json;
    json_object *jarray;
    json_object *tmp;
    json_object *statistics;
    json_object *count;

    // Converting data to Json Object type
    parsed_json = json_tokener_parse(buffer);

    // Executing "items" array from json structure
    json_object_object_get_ex(parsed_json, "items", &jarray);

    // Executing first element of array which contents statistics
    jarray = json_object_array_get_idx(jarray, 0);

    // Executing statistics - needed section
    json_object_object_get_ex(jarray, "statistics", &statistics);


    //printf("Object: %s \n", json_object_get_string(statistics)); // Checking emptyness

    // Discover execution target
    if(target == 0){
        // Executing views
        json_object_object_get_ex(statistics, "viewCount", &count);
        //printf("Views: %s \n", json_object_to_json_string(count));
    }else if(target == 1){
        // Executing likes
        json_object_object_get_ex(statistics, "likeCount", &count);
        //printf("Likes: %s \n", json_object_to_json_string(count));
    }else if(target == 2){
        // Executing dislikes
        json_object_object_get_ex(statistics, "dislikeCount", &count);
        //printf("Dislikes: %s \n", json_object_to_json_string(count));
    }else if(target == 3){
        // Executing comments
        json_object_object_get_ex(statistics, "commentCount", &count);
        //printf("Comments: %s \n", json_object_to_json_string(count));
    }

    // Converting Json object to integer
    int res = json_object_get_int(count);
    
    fclose(json);

    return res;
}
