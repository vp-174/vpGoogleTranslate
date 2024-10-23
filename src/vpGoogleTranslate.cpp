#include "vpGoogleTranslate.h"

vp::vpGoogleTranslate::vpGoogleTranslate() {
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL" << std::endl;
    }
    userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36";
}

vp::vpGoogleTranslate::~vpGoogleTranslate() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t vp::vpGoogleTranslate::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    if (userp == nullptr) {
        std::cerr << "User pointer is null" << std::endl;
        return 0; // error
    }
    size_t totalSize = size * nmemb;
    ((std::string*)userp)->append((char*)contents, totalSize);
    return totalSize;
}

std::string vp::vpGoogleTranslate::translate(const std::string& text, const std::string& srcLang, const std::string& destLang) {
    if (!curl) {
        std::cerr << "cURL is not initialized" << std::endl;
        return "";
    }

    std::string url = "https://translate.google.com/translate_a/single?client=gtx&sl=" + srcLang + "&tl=" + destLang + "&dt=t&q=" + curl_easy_escape(curl, text.c_str(), text.length());
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    try {
        nlohmann::json jsonData = nlohmann::json::parse(response);
        if (!jsonData.is_array() || jsonData.empty()) {
            std::cerr << "Invalid JSON response" << std::endl;
            return "";
        }
        nlohmann::json sentences = jsonData[0];
        if (!sentences.is_array() || sentences.empty()) {
            std::cerr << "Invalid JSON response" << std::endl;
            return "";
        }
        nlohmann::json translation = sentences[0];
        if (!translation.is_array() || translation.empty()) {
            std::cerr << "Invalid JSON response" << std::endl;
            return "";
        }
        return translation[0].get<std::string>();
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return "";
    }
}