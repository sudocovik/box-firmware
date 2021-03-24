#include <Card.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

Card::Card(MFRC522::Uid uid) {
    UID = uidToHexString(uid);
}

String Card::uidToHexString(MFRC522::Uid uid) {
    if (uid.size == 0) return "";

    String hexString = "";

    for(unsigned short int i = 0; i < uid.size; i++) {
        const char prefix = uid.uidByte[i] < 10 ? '0' : '\0';

        String byteAsHexString = prefix + String(uid.uidByte[i], HEX);
        hexString += byteAsHexString + " ";
    }

    hexString.trim();
    hexString.toUpperCase();
    hexString.replace(' ', '-');

    return hexString;
}

bool Card::isUidValid() {
    return UID.isEmpty() == false;
}

String Card::toUid() const {
    return UID;
}

Card::AuthorizationResult Card::authorize() const {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://192.168.1.2/api/authorize-card");

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int responseCode = http.POST("uid=" + toUid());

    bool successful = responseCode > 0
                    ? http.getString() == "yaay!"
                    : false;

    http.end();

    /*
     * return POST.request()
     *            .to("http://192.168.1.2/api/authorize-card")
     *            .withHeader("Content-Type", "application/x-www-form-urlencoded")
     *            .andPayload("uid=" + toUid())
     *            .responseShouldBe("yaay")
     *                  ? authorizationSuccessful()
     *                  : authorizationFailed()
     */

    return Card::AuthorizationResult(successful);
}

Card::AuthorizationResult Card::authorizationSucceeded() {
    return Card::AuthorizationResult(true);
}

Card::AuthorizationResult Card::authorizationFailed() {
    return Card::AuthorizationResult(true);
}

Card::AuthorizationResult::AuthorizationResult(bool isSuccessful) {
    successful = isSuccessful;
}

Card::AuthorizationResult& Card::AuthorizationResult::onSuccess(void (*callback)()) {
    if (successful) {
        callback();
    }

    return *this;
}

Card::AuthorizationResult& Card::AuthorizationResult::onFailure(void (*callback)()) {
    if (!successful) {
        callback();
    }

    return *this;
}
