#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <CardReader.h>
#include <Card.h>

CardReader::CardReader(byte chipSelectPin, byte resetPowerDownPin) {
    reader = MFRC522(chipSelectPin, resetPowerDownPin);
}

void CardReader::begin() {
    SPI.begin();
    reader.PCD_Init();
    delay(4);
}

void CardReader::onSuccessfulAttempt(void (*callback)(Card)) {
    successfulAttemptCallback = callback;
}

void CardReader::onFailedAttempt(void (*callback)()) {
    failedAttemptCallback = callback;
}

void CardReader::onAnyAttempt(void (*callback)()) {
    anyAttemptCallback = callback;
}

void CardReader::tryReadingTheCard() {
    if (reader.PICC_IsNewCardPresent() == false)
        return;

    if (reader.PICC_ReadCardSerial() == false) {
        failedAttemptCallback();
        anyAttemptCallback();
        return;
    }

    /*
     *   If we got here it means the card is present and
     *   we should try to read UID and convert it to human readable HEX string.
     *   Disengaging with the card is required because we read all the information needed.
     */
    Card card = Card(reader.uid);

    reader.PICC_HaltA();

    if (card.isUidValid()) {
        successfulAttemptCallback(card);
    }
    else {
        failedAttemptCallback();
    }

    anyAttemptCallback();
}
