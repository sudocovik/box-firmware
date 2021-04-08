#ifndef AUTHORIZER_H
#define AUTHORIZER_H

class CardAuthorizer {
    public:
        class Result;

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
