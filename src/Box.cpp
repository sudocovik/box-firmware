#include <Arduino.h>
#include <Box.h>

Box::Box(byte lockPin, byte statePin) {
    _lockPin = lockPin;
    _statePin = statePin;
}

bool Box::isClosed() const {
    return !digitalRead(_statePin);
}
