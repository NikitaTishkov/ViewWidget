#include "GetData.h"
#include "JsonParser.h"

int main(int argc, char** argv){
    char* id = "Q2c6R9sfRZM";
    GetFromApi(id);

    GetFromJSON("viewCount");
    return 0;
}