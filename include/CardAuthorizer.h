#ifndef AUTHORIZER_H
#define AUTHORIZER_H

#include <Arduino.h>

class CardAuthorizer {
    private:
        String _uid;

    public:
        class Result;

        CardAuthorizer& giveUid(const String& uid);

        CardAuthorizer::Result authorize();
};

class CardAuthorizer::Result {
    private:
        bool successful;

    public:
        explicit Result(bool isSuccessful);

        Result& onSuccess(void (*callback)());

        Result& onFailure(void (*callback)());
};

#endif
