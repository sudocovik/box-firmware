#include <POST.h>
#include <Arduino.h>

POST::POST(): _wifiClient(), _httpClient() {
}

POST::~POST() {
    _httpClient.end();
}

POST POST::request() {
    return {};
}

POST& POST::to(const String& url) {
    _httpClient.begin(_wifiClient, url);
    _httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

    return *this;
}

POST& POST::withPayload(const String& payload) {
    _payload = payload;

    return *this;
}

uint8_t POST::responseCode() {
    return _httpClient.POST(_payload);
}
