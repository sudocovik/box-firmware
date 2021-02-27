#include <Arduino.h>
#include <CardReader.h>
#include <Box.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <NetworkManager.h>

#define RST_PIN     D1
#define SS_PIN      D2

#define STATE_PIN   D4
#define LOCK_PIN    D8

#define ACCESS_POINT_NAME       "BoxAP"
#define ACCESS_POINT_PASSWORD   "password"

CardReader reader = CardReader(SS_PIN, RST_PIN);
Box box = Box(LOCK_PIN, STATE_PIN);

String httpGETRequest(const char* url);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    box.configurePins();
    reader.begin();
    reader.dump();

    NetworkManager manager(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
    manager.connect([]() {
        Serial.println("Successfully connected to network!");
    });
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](const String uid) {
        Serial.println("Detected new card with UID: " + uid);

        if (box.isOpened()) {
            Serial.println("Box is opened, skipping...");
            return;
        }

        Serial.println("Box is closed, authorizing card with the server...");

        if (httpGETRequest("http://192.168.1.2/api/test") == "yaay!") {
            box.unlock();
            delay(4000);
            box.lock();
        }
    });
}

String httpGETRequest(const char* url) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
}