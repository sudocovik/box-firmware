#include <POST.h>

POST POST::request() {
    return {};
}

POST& POST::to(const char *url) {
    _url = url;

    return *this;
}

POST& POST::withPayload(const char *payload) {
    _payload = payload;

    return *this;
}
