#ifndef CARDREADER_H
#define CARDREADER_H

#include <MFRC522.h>

class CardReader {
    private:
        MFRC522 reader;
        unsigned long pauseTime;

        static String uidToHexString(MFRC522::Uid uid);

    public:
        CardReader(
                byte chipSelectPin,
                byte resetPowerDownPin
        );

        void begin();

        void dump();

        void pauseAfterSuccessfulRead(unsigned long milliseconds);

        void onCardDetected(void (*callback)(const String));
};

#endif
