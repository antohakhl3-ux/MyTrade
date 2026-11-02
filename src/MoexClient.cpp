#include "MoexClient.hpp"
#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::string*) userp)-> append((char*)contents, size * nmemb);
    return size * nmemb;
}

MoexClient::MoexClient(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
MoexClient::~MoexClient(){
    curl_global_cleanup();
}

std::string MoexClient::fetchHistory(const std::string& ticker){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl){
        std::string url = "https://www.moex.com/iss/engines/stock/markets/shares/boards/TQBR/securities/" + ticker + ".json";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36");
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK){
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return readBuffer;
}