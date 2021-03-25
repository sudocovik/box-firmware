#include <POST.h>

POST POST::request() {
    return {};
}

POST& POST::to(const char *url) {
    _url = url;

    return *this;
}
