#include <POST.h>
#include <Arduino.h>
#include <utility>

POST::POST(): _wifiClient(), _httpClient() {
}

POST POST::request() {
    return {};
}

POST& POST::to(String url) {
    _url = std::move(url);

    return *this;
}

POST& POST::withPayload(String payload) {
    _payload = std::move(payload);

    return *this;
}

String POST::response() {
    _httpClient.begin(_wifiClient, _url);
    _httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int responseCode = _httpClient.POST(_payload);

    String response = responseCode == 200
                                    ? _httpClient.getString()
                                    : "";

    _httpClient.end();

    return response;
}
