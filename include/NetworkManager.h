#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <Arduino.h>

class NetworkManager {
    private:
        typedef struct {
            char const* name;
            char const* password;
        } AP;

        AP accessPoint = {};

    public:
        NetworkManager(char const* accessPointName, char const* accessPointPassword);

        void connect(void (*onSuccess)()) const;
};

#endif
