#include <BoxAuthorizer.h>
#include <POST.h>

BoxAuthorizer::Result BoxAuthorizer::authorizationSucceeded() {
    return BoxAuthorizer::Result(true);
}

BoxAuthorizer::Result BoxAuthorizer::authorizationFailed() {
    return BoxAuthorizer::Result(false);
}

BoxAuthorizer::Result BoxAuthorizer::authorize(const String &uid) {
    return POST::request()
                 .to("http://165.227.172.159/api/box/authorize")
                 .withPayload("uid=" + uid)
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
