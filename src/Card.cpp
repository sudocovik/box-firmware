#include <Card.h>
#include <MFRC522.h>
#include <CardAuthorizer.h>

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

/*
Card::AuthorizationResult Card::authorize() const {
    return POST::request()
                .to("http://192.168.1.2/api/authorize-card")
                .withPayload("uid=" + toUid())
                .response().equals("yaay!")
                            ? authorizationSucceeded()
                            : authorizationFailed();
}

Card::AuthorizationResult Card::authorizationSucceeded() {
    return Card::AuthorizationResult(true);
}

Card::AuthorizationResult Card::authorizationFailed() {
    return Card::AuthorizationResult(false);
}
 */

CardAuthorizer::Result Card::authorize() const {
    return CardAuthorizer()
            .giveUid(toUid())
            .authorize();
}

