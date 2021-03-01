#include <StatusLED.h>

StatusLED::StatusLED(byte greenPin, byte redPin) {
    _greenPin = greenPin;
    _redPin = redPin;
}

void StatusLED::configurePins() const {
    pinMode(_greenPin, OUTPUT);
    pinMode(_redPin, OUTPUT);
}

StatusLED StatusLED::idle() const {
    analogWrite(_greenPin, 10);
    redOff();

    return *this;
}

void StatusLED::greenOn() const {
    analogWrite(_greenPin, 550);
}

void StatusLED::greenOff() const {
    analogWrite(_greenPin, 0);
}

void StatusLED::redOn() const {
    digitalWrite(_redPin, HIGH);
}

void StatusLED::redOff() const {
    digitalWrite(_redPin, LOW);
}
