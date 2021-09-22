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

    reader.PCD_DumpVersionToSerial();
}

CardReader& CardReader::onSuccessfulAttempt(void (*callback)(const Card&)) {
    successfulAttemptCallback = callback;

    return *this;
}

CardReader& CardReader::onFailedAttempt(void (*callback)()) {
    failedAttemptCallback = callback;

    return *this;
}

CardReader& CardReader::onAnyAttempt(void (*callback)()) {
    anyAttemptCallback = callback;

    return *this;
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
     *   If we got here it means the card is present.
     *   We should try to read UID and convert it to human-readable HEX string.
     *   Disengaging with the card is required because we read all the information needed.
     */
    Card card = Card(reader.uid);

    reader.PICC_HaltA();
    reader.PCD_StopCrypto1();

    if (card.isUidValid()) {
        successfulAttemptCallback(card);
    }
    else {
        failedAttemptCallback();
    }

    anyAttemptCallback();
}
