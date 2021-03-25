#include <POST.h>
#include <Arduino.h>
#include <utility>

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

POST& POST::withPayload(String payload) {
    _payload = std::move(payload);

    return *this;
}

String POST::response() {
    int responseCode = _httpClient.POST(_payload);

    String response = responseCode == 200
                                    ? _httpClient.getString()
                                    : "";

    return response;
}
