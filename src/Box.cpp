#include <Arduino.h>
#include <Box.h>

Box::Box(byte lockPin, byte statePin) {
    _lockPin = lockPin;
    _statePin = statePin;
}

bool Box::isClosed() const {
    return !digitalRead(_statePin);
}

void Box::unlock() const {
    digitalWrite(_lockPin, HIGH);
}

void Box::lock() const {
    digitalWrite(_lockPin, LOW);
}
