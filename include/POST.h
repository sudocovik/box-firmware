#ifndef POST_H
#define POST_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

class POST {
    private:
        String _payload;

        WiFiClient _wifiClient;

        HTTPClient _httpClient;

    public:
        POST();

        static POST request();

        POST& to(const String& url);

        POST& withPayload(String payload);

        String response();
};

#endif
