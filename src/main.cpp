#include <Arduino.h>
#include <Box.h>
#include <CardReader.h>
#include <NetworkManager.h>
#include <StatusLED.h>

#define RST_PIN     0
#define SS_PIN      5

#define LOCK_PIN    13
#define STATE_PIN   33

#define RED_PIN     27
#define GREEN_PIN   26
#define BLUE_PIN    25

#define ACCESS_POINT_NAME       "BoxAP"
#define ACCESS_POINT_PASSWORD   "password"


BoxAuthorizer authorizer = BoxAuthorizer();
Box box = Box(LOCK_PIN, STATE_PIN, authorizer);
CardReader reader = CardReader(SS_PIN, RST_PIN);
StatusLED LED = StatusLED(GREEN_PIN, RED_PIN, BLUE_PIN);


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

void tryToAuthorizeAccess(const Card& card) {
    Serial.println("--------------------------------------------------");
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

    box.authorize(card)
       .onSuccess(grantAccess)
       .onFailure(notifyForbiddenAccess);
}

void indicateCardReadingFailure() {
    Serial.println("Card present on the reader but failed to read the UID.");
    LED.flashRed(2);
}

void resetLED() {
    LED.idle();
}

void setup() {
    Serial.begin(9600);

    box.configurePins();

    LED.configurePins();
    LED.idle();

    reader.begin();
    reader.onSuccessfulAttempt(tryToAuthorizeAccess)
          .onFailedAttempt(indicateCardReadingFailure)
          .onAnyAttempt(resetLED);

    NetworkManager manager = NetworkManager(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
    manager.connect([]() {
        Serial.println("Successfully connected to network!");
    });
}

void loop() {
    reader.tryReadingTheCard();
    delay(1000);
}