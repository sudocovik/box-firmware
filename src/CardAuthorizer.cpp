#include <CardAuthorizer.h>

CardAuthorizer &CardAuthorizer::giveUid(const String& uid) {
    _uid = uid;

    return *this;
}

CardAuthorizer::Result CardAuthorizer::authorize() {
    Serial.println("Auth uid:" + _uid);

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
