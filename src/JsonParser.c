
#include <stdio.h>
#include <json-c/json.h>
#include "JsonParser.h"

char* GetFromJSON(char* target){
    FILE* json = fopen("temp.json", "r");
    char buffer[2048];
    
    //fseek(json,0,SEEK_END);
    //int size_json = ftell(json);
    
    fread(buffer, 2048, 1, json);
    printf("Buffer: %s \n", buffer);
    struct json_object *parsed_json;
    struct json_object *value;

    parsed_json = json_tokener_parse(buffer);

    value = json_object_object_get(parsed_json, target);

    char* res = json_object_get_string(value);

    printf("Data: %s \n", res);
}

