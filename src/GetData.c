
// A function that gets data(statistics) about youtube object
// This function makes an https request to Youtube Data Api to get
//                                            needed information
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "GetData.h"
// Including libcurl library to use the request methods



void GetFromApi(const char* id)
{
    FILE* data = fopen("temp.json", "w");
    // Creating json file fow saving data
    CURL *curl = curl_easy_init();
    // Initialization cURL

    char url[256];
    //Making an url for our request
    sprintf(url, "https://www.googleapis.com/youtube/v3/videos?id=%s&key=%s&part=statistics", id, API_KEY);

    //Set our url for request
    CURLcode res1 = curl_easy_setopt(curl, CURLOPT_URL, url);

    //Checking for correct setting arguments to cURL object
    if (res1 != CURLE_OK) {
        fprintf(stderr ,"Setting url error: %s \n", curl_easy_strerror(res1));
    }

    //Set a type of request to GET
    CURLcode res2 = curl_easy_setopt(curl, CURLOPT_HTTPGET, 0);


    if (res2 != CURLE_OK) {
        fprintf(stderr ,"Setting url error: %s \n", curl_easy_strerror(res2));
    }

    //Set file for saving data
    CURLcode res3 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

    if (res3 != CURLE_OK) {
        fprintf(stderr ,"Setting url error: %s \n", curl_easy_strerror(res3));
    }

    //Swigtch on verbose mode
    CURLcode res4 = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

    if (res4 != CURLE_OK) {
        fprintf(stderr ,"Setting url error: %s \n", curl_easy_strerror(res4));
    }

    //making the request
    CURLcode res5 = curl_easy_perform(curl);

    if (res5 != CURLE_OK) {
        fprintf(stderr ,"Setting url error: %s \n", curl_easy_strerror(res5));
    }

    //deallocation:
    curl_easy_cleanup(curl);
    fclose(data);

}
