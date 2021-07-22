#include <StatusLED.h>
#include <Arduino.h>

StatusLED::StatusLED(byte greenPin, byte redPin, byte bluePin) {
    _greenPin = greenPin;
    _redPin = redPin;
    _bluePin = bluePin;
}

void StatusLED::configurePins() const {
    ledcSetup(_greenChannel, 5000, 8);
    ledcAttachPin(_greenPin, _greenChannel);

    ledcSetup(_redChannel, 5000, 8);
    ledcAttachPin(_redPin, _redChannel);

    ledcSetup(_blueChannel, 5000, 8);
    ledcAttachPin(_bluePin, _blueChannel);
}

StatusLED StatusLED::idle() const {
    ledcWrite(_redChannel, 255);
    ledcWrite(_greenChannel, 127);
    ledcWrite(_blueChannel, 0);

    return *this;
}

void StatusLED::greenOn() const {
    ledcWrite(_greenChannel, 255);
}

void StatusLED::greenOff() const {
    ledcWrite(_greenChannel, 0);
}

void StatusLED::redOn() const {
    ledcWrite(_redChannel, 255);
}

void StatusLED::redOff() const {
    ledcWrite(_redChannel, 0);
}

void StatusLED::blueOn() const {
    ledcWrite(_blueChannel, 255);
}

void StatusLED::blueOff() const {
    ledcWrite(_blueChannel, 0);
}

StatusLED StatusLED::flashGreen(unsigned short int times) const {
    if (times == 0) return *this;

    redOff();

    for (unsigned short int i = 0; i < times; i++) {
        greenOn();
        delay(200);
        greenOff();
        delay(200);
    }

    return *this;
}

StatusLED StatusLED::flashRed(unsigned short int times) const {
    if (times == 0) return *this;

    greenOff();

    for (unsigned short int i = 0; i < times; i++) {
        redOn();
        delay(200);
        redOff();
        delay(200);
    }

    return *this;
}
