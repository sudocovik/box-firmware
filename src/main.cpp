#include <Arduino.h>
#include <CardReader.h>
#include <Box.h>

#define RST_PIN     D1
#define SS_PIN      D2

#define STATE_PIN   D4
#define LOCK_PIN    D8

CardReader reader = CardReader(SS_PIN, RST_PIN);
Box box = Box(LOCK_PIN, STATE_PIN);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    box.configurePins();
    reader.begin();
    reader.dump();
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](const String uid) {
        Serial.println("Detected new card with UID: " + uid);

        if (box.isClosed()) {
            Serial.println("Box is closed, authorizing card with the server...");

            // Imagine successful authorization
            box.unlock();
            delay(4000);
            box.lock();
        }
        else {
            Serial.println("Box is opened, skipping...");
        }
    });
}