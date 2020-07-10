#include "GetData.h"
#include "JsonParser.h"
#include <stdio.h>
int main(int argc, char** argv){
    char* id = "Q2c6R9sfRZM";
    GetFromApi(id);

    int viewCount = GetFromJSON_statistics("likes");
    //views likes dislikes comments
    printf("Count: %d \n", viewCount);
    return 0;
}