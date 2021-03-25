#ifndef POST_H
#define POST_H

class POST {
    private:
        const char* _url;

    public:
        static POST request();

        POST& to(const char* url);
};

#endif
