#include <Arduino.h>
#include <CardReader.h>
#include <Box.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define RST_PIN     D1
#define SS_PIN      D2

#define STATE_PIN   D4
#define LOCK_PIN    D8

CardReader reader = CardReader(SS_PIN, RST_PIN);
Box box = Box(LOCK_PIN, STATE_PIN);

String httpGETRequest(const char* url);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    box.configurePins();
    reader.begin();
    reader.dump();

    WiFiManager wifiManager;
    bool connected = wifiManager.autoConnect("BoxAP", "password");

    if (connected) {
        Serial.println("Successfully connected to network!");
    }
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](const String uid) {
        Serial.println("Detected new card with UID: " + uid);

        if (box.isClosed()) {
            Serial.println("Box is closed, authorizing card with the server...");

            if (httpGETRequest("http://192.168.1.2/api/test") == "yaay!") {
                box.unlock();
                delay(4000);
                box.lock();
            }
        }
        else {
            Serial.println("Box is opened, skipping...");
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