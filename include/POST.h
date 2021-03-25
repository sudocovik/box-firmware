#ifndef POST_H
#define POST_H

class POST {
    private:
        const char* _url;

        const char* _payload;

    public:
        static POST request();

        POST& to(const char* url);

        POST& withPayload(const char* payload);
};

#endif
