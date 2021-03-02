#ifndef CARDREADER_H
#define CARDREADER_H

#include <MFRC522.h>
#include <Card.h>

class CardReader {
    private:
        MFRC522 reader;

        void (*successfulAttemptCallback)(Card);

        void (*failedAttemptCallback)();

        void (*anyAttemptCallback)();

    public:
        CardReader(
                byte chipSelectPin,
                byte resetPowerDownPin
        );

        void begin();

        CardReader onSuccessfulAttempt(void (*callback)(Card));

        CardReader onFailedAttempt(void (*callback)());

        CardReader onAnyAttempt(void (*callback)());

        void tryReadingTheCard();
};

#endif
