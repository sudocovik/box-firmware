#include <Arduino.h>
#include <CardReader.h>
#include <Box.h>
#include <NetworkManager.h>
#include <StatusLED.h>

#define RST_PIN     D1
#define SS_PIN      D2

#define GREEN_PIN   D3
#define RED_PIN     D0

#define STATE_PIN   D4
#define LOCK_PIN    D8

#define ACCESS_POINT_NAME       "BoxAP"
#define ACCESS_POINT_PASSWORD   "password"

CardReader reader = CardReader(SS_PIN, RST_PIN);
Box box = Box(LOCK_PIN, STATE_PIN);
StatusLED LED = StatusLED(GREEN_PIN, RED_PIN);

void grantAccess() {
    Serial.println("Successful authorization! Opening the box...");

    LED.flashGreen(2);

    box.unlock();
    delay(4000);
    box.lock();
}

void notifyForbiddenAccess() {
    Serial.println("Failed authorization!");
    LED.flashRed(3);
}

void tryToAuthorizeAccess(Card card) {
    Serial.println("Detected new card with UID: " + card.toUid());

    LED.flashGreen(1);
    delay(1000);
    LED.idle();

    if (box.isOpened()) {
        Serial.println("Box is opened, skipping...");
        LED.flashRed(1);
        return;
    }

    Serial.println("Box is closed, authorizing card with the server...");

    card.authorize()
        .onSuccess(grantAccess)
        .onFailure(notifyForbiddenAccess);

    LED.idle();
}

void indicateCardReadingFailure() {
    Serial.println("Card present on the reader but failed to read the UID.");
    LED.flashRed(2);
}

void setup() {
    Serial.begin(9600);
    while (!Serial);

    box.configurePins();
    LED.configurePins();
    LED.idle();
    reader.begin();
    reader.dump();

    NetworkManager manager = NetworkManager(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
    manager.connect([]() {
        Serial.println("Successfully connected to network!");
    });

    reader.pauseAfterSuccessfulRead(2000);
    reader.onSuccessfulAttempt(tryToAuthorizeAccess);
    reader.onFailedAttempt(indicateCardReadingFailure);
}

void loop() {
    reader.tryReadingTheCard();
}
