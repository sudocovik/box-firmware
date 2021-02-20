#include <Arduino.h>
#include <CardReader.h>

#define RST_PIN     D1
#define SS_PIN      D2

CardReader reader = CardReader(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    reader.begin();
    reader.dump();
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](String uid) {
        Serial.println("Detected new card with UID: " + uid);
    });
}