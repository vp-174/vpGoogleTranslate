/*
 * Библиотека: vpGoogleTranslate
 * Автор: Vladislav Panov
 * Версия: 1.0
*/

#ifndef VPGOOGLETRANSLATE_H
#define VPGOOGLETRANSLATE_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

namespace vp {

    class vpGoogleTranslate {
    public:
        vpGoogleTranslate();
        ~vpGoogleTranslate();
        std::string translate(const std::string& text, const std::string& srcLang, const std::string& destLang);
        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    private:
        CURL* curl;
        std::string userAgent;
    };

} // namespace vp

#endif  // VPGOOGLETRANSLATE_H
