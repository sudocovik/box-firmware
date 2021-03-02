#ifndef CARDREADER_H
#define CARDREADER_H

#include <MFRC522.h>
#include <Card.h>

class CardReader {
    private:
        MFRC522 reader;

        unsigned long pauseTime;

        void (*successfulAttemptCallback)(Card);

        void (*failedAttemptCallback)();

    public:
        CardReader(
                byte chipSelectPin,
                byte resetPowerDownPin
        );

        void begin();

        void dump();

        void pauseAfterSuccessfulRead(unsigned long milliseconds);

        void onSuccessfulAttempt(void (*callback)(Card));

        void onFailedAttempt(void (*callback)());

        void tryReadingTheCard();
};

#endif
