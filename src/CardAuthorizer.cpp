#include <CardAuthorizer.h>

CardAuthorizer::Result CardAuthorizer::authorize() {
    return CardAuthorizer::Result(false);
}

CardAuthorizer::Result::Result(bool isSuccessful) {
    successful = isSuccessful;
}

CardAuthorizer::Result& CardAuthorizer::Result::onSuccess(void (*callback)()) {
    if (successful) {
        callback();
    }

    return *this;
}

CardAuthorizer::Result& CardAuthorizer::Result::onFailure(void (*callback)()) {
    if (!successful) {
        callback();
    }

    return *this;
}
