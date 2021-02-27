#ifndef CARD_H
#define CARD_H

#include <MFRC522.h>

class Card {
    private:
        String UID = "";

        static String uidToHexString(MFRC522::Uid uid);

    public:
        explicit Card(MFRC522::Uid uid);
};

#endif
