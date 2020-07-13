
// A function that gets data(statistics) about youtube object
// This function makes an https request to Youtube Data Api to get
//                                            needed information
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "GetData.h"
// Including libcurl library to use the request methods

//#define API_KEY "AIzaSyBgxTSi0WNEyNNN7JyuimLMgk9XMGT2bjI"
// An API key for connection
void GetFromApi(const char* id){
    FILE* data = fopen("temp.json", "w");
    // Creating json file fow saving data
    CURL *curl = curl_easy_init();
    // Initialization cURL

    char url[256];
    sprintf(url, "https://www.googleapis.com/youtube/v3/videos?id=%s&key=%s&part=statistics", id, API_KEY);
    //Making an url for our request

    CURLcode res1 = curl_easy_setopt(curl, CURLOPT_URL, url);
    //Set our url for request
    //printf("1: %s \n", curl_easy_strerror(res1));

    CURLcode res2 = curl_easy_setopt(curl, CURLOPT_HTTPGET, 0);
    //Set a type of request to GET
    //printf("2: %s \n", curl_easy_strerror(res2));

    CURLcode res3 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    //Set file for saving data
    //printf("3: %s \n", curl_easy_strerror(res3));
    CURLcode res4 = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    //Swigtch on verbose mode
    //printf("4: %s \n", curl_easy_strerror(res4));
    CURLcode res5 = curl_easy_perform(curl);
    //make the request
    //printf("5: %s \n", curl_easy_strerror(res5));

    curl_easy_cleanup(curl);
    fclose(data);
    //deallocation
}
