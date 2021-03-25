#include <POST.h>
#include <Arduino.h>
#include <utility>

POST POST::request() {
    return {};
}

POST& POST::to(String url) {
    _url = std::move(url);

    return *this;
}

POST& POST::withPayload(String payload) {
    _payload = std::move(payload);

    return *this;
}
