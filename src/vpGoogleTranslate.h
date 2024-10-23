/*
 * Библиотека: vpGoogleTranslate
 * Автор: Vladislav Panov
 * Версия: 1.0
 * 
 * Описание:
 * vpGoogleTranslate - это C++ библиотека, предназначенная для выполнения переводов текста с использованием 
 * API Google Translate. Библиотека использует cURL для выполнения HTTP-запросов и nlohmann/json (Niels Lohmann)
 * для обработки JSON-ответов.
 * 
 * Основные функции:
 * - translate: переводит заданный текст с одного языка на другой.
 * 
 * Использование:
 * 1. Создайте объект класса vpGoogleTranslate.
 * 2. Вызовите метод translate, передав текст для перевода, исходный язык и язык назначения.
 * 
 * Пример:
 * vp::vpGoogleTranslate translator;
 * std::string translatedText = translator.translate("Hello", "en", "ru");
 * std::cout << translatedText << std::endl; // Вывод: "Привет"
 * 
 * Лицензия: MIT License
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