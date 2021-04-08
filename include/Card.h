#ifndef CARD_H
#define CARD_H

#include <MFRC522.h>
#include <CardAuthorizer.h>

class Card {
    private:
        String UID = "";

        static String uidToHexString(MFRC522::Uid uid);

        /*static Card::AuthorizationResult authorizationSucceeded();

        static Card::AuthorizationResult authorizationFailed();*/

    public:
        explicit Card(MFRC522::Uid uid);

        bool isUidValid();

        String toUid() const;

        CardAuthorizer::Result authorize() const;
};

#endif
