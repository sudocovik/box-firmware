#ifndef CARD_H
#define CARD_H

#include <MFRC522.h>

class Card {
    private:
        String UID = "";

        class AuthorizationResult;

        static String uidToHexString(MFRC522::Uid uid);

        Card::AuthorizationResult authorizationSuccessful();

        Card::AuthorizationResult authorizationFailed();

    public:
        explicit Card(MFRC522::Uid uid);

        bool isUidValid();

        String toUid() const;

        Card::AuthorizationResult authorize() const;
};

class Card::AuthorizationResult {
    private:
        bool successful;

    public:
        explicit AuthorizationResult(bool isSuccessful);

        Card::AuthorizationResult& onSuccess(void (*callback)());

        Card::AuthorizationResult& onFailure(void (*callback)());
};

#endif
