#include <CardAuthorizer.h>
#include <POST.h>

CardAuthorizer &CardAuthorizer::giveUid(const String& uid) {
    _uid = uid;

    return *this;
}

CardAuthorizer::Result CardAuthorizer::authorizationSucceeded() {
    return CardAuthorizer::Result(true);
}

CardAuthorizer::Result CardAuthorizer::authorizationFailed() {
    return CardAuthorizer::Result(false);
}

CardAuthorizer::Result CardAuthorizer::authorize() {
    return POST::request()
                 .to("http://192.168.1.2/api/authorize-card")
                 .withPayload("uid=" + _uid)
                 .response().equals("yaay!")
                            ? authorizationSucceeded()
                            : authorizationFailed();
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
