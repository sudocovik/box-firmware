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
}

void grantAccess() {
    Serial.println("Successful authorization! Opening the box...");

    box.unlock();
    delay(4000);
    box.lock();
}

void notifyForbiddenAccess() {
    Serial.println("Failed authorization!");
}

void loop() {
    reader.pauseAfterSuccessfulRead(2000);

    reader.onCardDetected([](Card card) {
        Serial.println("Detected new card with UID: " + card.toUid());

        if (box.isOpened()) {
            Serial.println("Box is opened, skipping...");
            return;
        }

        Serial.println("Box is closed, authorizing card with the server...");

        card.authorize()
            .onSuccess(grantAccess)
            .onFailure(notifyForbiddenAccess);

        LED.idle();
    });
}
