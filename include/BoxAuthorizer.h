#ifndef BOX_AUTHORIZER_H
#define BOX_AUTHORIZER_H

#include <Arduino.h>

class BoxAuthorizer {
    public: class Result;

    private:
        static BoxAuthorizer::Result authorizationSucceeded();

        static BoxAuthorizer::Result authorizationFailed();

    public:
        BoxAuthorizer::Result authorize(const String& uid);
};

class BoxAuthorizer::Result {
    private:
        bool successful;

    public:
        explicit Result(bool isSuccessful);

        Result& onSuccess(void (*callback)());

        Result& onFailure(void (*callback)());
};

#endif
