
#include <stdio.h>
#include <json-c/json.h>
#include "JsonParser.h"


int GetFromJSON_statistics(int target){
    FILE* json = fopen("temp.json", "r");
    char buffer[2048];



    fread(buffer, 2048, 1, json);
    //printf("Buffer: %s \n", buffer);
    json_object *parsed_json;
    json_object *jarray;
    json_object *tmp;
    json_object *statistics;
    json_object *count;
    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "items", &jarray);

    jarray = json_object_array_get_idx(jarray, 0);

    json_object_object_get_ex(jarray, "statistics", &statistics);

    printf("Object: %s \n", json_object_get_string(statistics));
    if(target == 0){
        json_object_object_get_ex(statistics, "viewCount", &count);
        printf("Views: %s \n", json_object_to_json_string(count));
    }else if(target == 1){
        json_object_object_get_ex(statistics, "likeCount", &count);
        printf("Likes: %s \n", json_object_to_json_string(count));
    }else if(target == 2){
        json_object_object_get_ex(statistics, "dislikeCount", &count);
        printf("Dislikes: %s \n", json_object_to_json_string(count));
    }else if(target == 3){
        json_object_object_get_ex(statistics, "commentCount", &count);
        printf("Comments: %s \n", json_object_to_json_string(count));
    }

    int res = json_object_get_int(count);
    fclose(json);
    return res;
}
