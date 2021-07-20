#include <Arduino.h>
#include <CardReader.h>

#define RST_PIN 0
#define SS_PIN 5

CardReader reader = CardReader(SS_PIN, RST_PIN);

void printUid(const Card &card) {
    Serial.println("UID:" + card.toUid());
}

void printFailure() {
    Serial.println("Failed to read the card");
}

void looool () {
    Serial.println("Test");
}

void setup() {
    Serial.begin(9600);

    reader.begin();
    reader.onSuccessfulAttempt(printUid)
            .onFailedAttempt(printFailure)
            .onAnyAttempt(looool);
}

void loop() {
    reader.tryReadingTheCard();
    delay(1000);
}