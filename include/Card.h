#ifndef CARD_H
#define CARD_H

#include <MFRC522.h>

class Card {
    private:
        String UID = "";

        class AuthorizationResult;

        static String uidToHexString(MFRC522::Uid uid);

    public:
        explicit Card(MFRC522::Uid uid);

        bool isUidValid();

        String toUid() const;

        Card::AuthorizationResult authorize();
};

class Card::AuthorizationResult {
    private:
        bool successful;

    public:
        explicit AuthorizationResult(bool isSuccessful);

        Card::AuthorizationResult onSuccess(void (*callback)());

        Card::AuthorizationResult onFailure(void (*callback)());
};

#endif
