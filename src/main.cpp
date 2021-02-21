#include <Arduino.h>
#include <CardReader.h>

#define RST_PIN     D1
#define SS_PIN      D2

#define GREEN_PIN   D3
#define RED_PIN     D0

CardReader reader = CardReader(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    while (!Serial);

    reader.begin();
    reader.dump();


    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    digitalWrite(RED_PIN, LOW);
    analogWrite(GREEN_PIN, 10);
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](String uid) {
        Serial.println("Detected new card with UID: " + uid);


        digitalWrite(RED_PIN, LOW);
        analogWrite(GREEN_PIN, 550);

        delay(200);

        analogWrite(GREEN_PIN, 0);

        delay(200);

        analogWrite(GREEN_PIN, 550);


        delay(2000);
        analogWrite(GREEN_PIN, 10);
    });
}