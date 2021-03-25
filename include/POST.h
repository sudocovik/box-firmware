#ifndef POST_H
#define POST_H

#include <Arduino.h>

class POST {
    private:
        String _url;

        String _payload;

    public:
        static POST request();

        POST& to(String url);

        POST& withPayload(String payload);

        POST& withPayload(const char* payload);
};

#endif
