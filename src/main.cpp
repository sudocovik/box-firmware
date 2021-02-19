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
    /*
    if (mfrc522.uid.size == 0) {
        Serial.println("Bad card (size = 0)");
    } else {
        char tag[sizeof(mfrc522.uid.uidByte) * 4] = { 0 };
        for (int i = 0; i < mfrc522.uid.size; i++) {
            char buff[5]; // 3 digits, dash and \0.
            snprintf(buff, sizeof(buff), "%s%d", i ? "-" : "", mfrc522.uid.uidByte[i]);
            strncat(tag, buff, sizeof(tag));
        };
        Serial.println("Good scan: ");
        Serial.println(tag);
    };
    */

    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([]() {
        Serial.println("Test");
    });
}