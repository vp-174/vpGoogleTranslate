# vpGoogleTranslate 1.0

C++ библиотека, предназначенная для выполнения переводов текста с использованием 
API Google Translate. Библиотека использует [curl](https://github.com/curl/curl) для выполнения HTTP-запросов и [nlohmann/json](https://github.com/nlohmann/json)
для обработки JSON-ответов.
 
```
// example.cpp

#include "vpGoogleTranslate.h"

int main() 
{
    vp::vpGoogleTranslate translator;
    std::string translatedText = translator.translate("Hello", "en", "ru");
    std::cout << translatedText << std::endl; 
    // > Привет

    return 0;
}
```
