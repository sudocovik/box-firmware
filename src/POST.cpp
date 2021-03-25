#include <POST.h>
#include <Arduino.h>
#include <utility>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

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
    WiFiClient client;
    HTTPClient http;

    http.begin(client, _url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int responseCode = http.POST(_payload);

    String response = responseCode == 200
                                    ? http.getString()
                                    : "";

    http.end();

    return response;
}


