#include <stdlib.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
const char* api_key = "AIzaSyBgxTSi0WNEyNNN7JyuimLMgk9XMGT2bjI";
void GetFromApi(char* id){
    FILE* data = fopen("temp.json", "w");
    CURL *curl = curl_easy_init();
    /*char* url = "https://www.googleapis.com/youtube/v3/videos?id=" + id 
                                                            + "&key="
                                                            + api_key
                                                            + "&part="
                                                            + "statistics";
                                                            */
    char url[] = "https://www.googleapis.com/youtube/v3/videos?id=";
    strcat(url, id);
    strcat(url,"&key=");
    strcat(url, api_key);
    strcat(url, "&part=");
    strcat(url, "statistics");
    CURLcode res1 = curl_easy_setopt(curl, CURLOPT_URL, url);
    printf("1: %s \n", curl_easy_strerror(res1));

    CURLcode res2 = curl_easy_setopt(curl, CURLOPT_HTTPGET, 0);
    printf("2: %s \n", curl_easy_strerror(res2));
    CURLcode res3 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    printf("3: %s \n", curl_easy_strerror(res3));
    CURLcode res4 = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    printf("4: %s \n", curl_easy_strerror(res4));
    CURLcode res5 = curl_easy_perform(curl);
    printf("5: %s \n", curl_easy_strerror(res5));
    curl_easy_cleanup(curl);

    fclose(data);
}

int main(int argc, char** argv){
    char* id = "kXYiU_JCYtU";
    GetFromApi(id);
    return 0;
}
