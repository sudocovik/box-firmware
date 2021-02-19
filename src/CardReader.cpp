#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <CardReader.h>

CardReader::CardReader(byte chipSelectPin, byte resetPowerDownPin) {
    reader = MFRC522(chipSelectPin, resetPowerDownPin);
}

void CardReader::dump() {
    reader.PCD_DumpVersionToSerial();
}

void CardReader::begin() {
    SPI.begin();
    reader.PCD_Init();
    delay(4);
}

void CardReader::pauseAfterSuccessfulRead(unsigned long milliseconds) {
    pauseTime = milliseconds;
}

void CardReader::onCardDetected(void (*callback)()) {
    if (reader.PICC_IsNewCardPresent() == false)
        return;

    if (reader.PICC_ReadCardSerial() == false)
        return;

    /*
     *   If we got here it means the card is present and was successfully read.
     *   Just invoke the callback that user supplied,
     *   halt the card and pause for a couple of seconds
     */
    callback();
    reader.PICC_HaltA();
    delay(pauseTime);
}
