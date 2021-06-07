#include <BoxAuthorizer.h>
#include <POST.h>

BoxAuthorizer &BoxAuthorizer::giveUid(const String& uid) {
    _uid = uid;

    return *this;
}

BoxAuthorizer::Result BoxAuthorizer::authorizationSucceeded() {
    return BoxAuthorizer::Result(true);
}

BoxAuthorizer::Result BoxAuthorizer::authorizationFailed() {
    return BoxAuthorizer::Result(false);
}

BoxAuthorizer::Result BoxAuthorizer::authorize() {
    return POST::request()
                 .to("http://192.168.1.2/api/box/authorize")
                 .withPayload("uid=" + _uid)
                 .responseCode() == 200
                                  ? authorizationSucceeded()
                                  : authorizationFailed();
}


BoxAuthorizer::Result::Result(bool isSuccessful) {
    successful = isSuccessful;
}

BoxAuthorizer::Result& BoxAuthorizer::Result::onSuccess(void (*callback)()) {
    if (successful) {
        callback();
    }

    return *this;
}

BoxAuthorizer::Result& BoxAuthorizer::Result::onFailure(void (*callback)()) {
    if (!successful) {
        callback();
    }

    return *this;
}
