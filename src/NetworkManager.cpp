#include <NetworkManager.h>
#include <WiFiManager.h>

NetworkManager::NetworkManager(char const* accessPointName, char const* accessPointPassword) {
    accessPoint.name = accessPointName;
    accessPoint.password = accessPointPassword;
}

void NetworkManager::connect(void (*onSuccess)()) const {
    WiFiManager manager;
    bool connectionSuccessful = manager.autoConnect(accessPoint.name, accessPoint.password);

    if (connectionSuccessful) {
        onSuccess();
    }
}


