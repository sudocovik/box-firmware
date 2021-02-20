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

void CardReader::onCardDetected(void (*callback)(String)) {
    if (reader.PICC_IsNewCardPresent() == false)
        return;

    if (reader.PICC_ReadCardSerial() == false)
        return;

    /*
     *   If we got here it means the card is present and
     *   we should try to read UID and convert it to human readable HEX string.
     *   Disengaging with the card is required because we read all the information needed.
     */
    String uid = uidToHexString(reader.uid);

    reader.PICC_HaltA();

    /*
     *   Empty UID string means something went wrong (bad card, error in the program, ...)
     *   while non-empty UID means we can invoke the callback that user supplied and pause for a couple of seconds
     */
    if (uid.isEmpty() == false) {
        callback(uid);
        delay(pauseTime);
    }
}

String CardReader::uidToHexString(MFRC522::Uid uid) {
    if (uid.size == 0) return "";

    String hexString = "";

    for(unsigned short int i = 0; i < uid.size; i++) {
        const char prefix = uid.uidByte[i] < 10 ? '0' : '\0';

        String byteAsHexString = prefix + String(uid.uidByte[i], HEX);
        hexString += byteAsHexString + " ";
    }

    hexString.trim();
    hexString.toUpperCase();

    return hexString;
}
