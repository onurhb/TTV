
// -------------- INCLUDES
#include <iostream>
#include "HTTP.h"


size_t callBack(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    }
    catch (std::bad_alloc &e) {
        return 0;
    }

    std::copy((char *) contents, (char *) contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}


HTTP_STATUS HTTP::get(std::string URL, bool follow) {

    // - Initialize curl
    response.clear();
    curl = curl_easy_init();
    status = HTTP_REJECTED;

    if (!curl) {
        std::cerr << "Curl is not initialized. Cannot perform HTTP request." << std::endl;
        curl_easy_cleanup(curl);
        return status;
    }

    // - Set options
    if(follow) {
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl,  CURLOPT_MAXREDIRS, 1);
    }
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // - Execute
    CURLcode res;
    res = curl_easy_perform(curl);

    // - Error
    if (res == CURLE_OK) status = HTTP_OK;

    // - Cleanup
    curl_easy_cleanup(curl);

    return status;
}

HTTP::HTTP() {

    // - Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HTTP::~HTTP() {
    curl_global_cleanup();
}

std::string HTTP::getResponse() const {
    return response;
}

