#ifndef STATUSLED_H
#define STATUSLED_H

#include <Arduino.h>

class StatusLED {
    private:
        byte _greenPin;

        byte _redPin;

        void greenOn() const;

        void greenOff() const;

        void redOn() const;

        void redOff() const;

    public:
        StatusLED(
            byte greenPin,
            byte redPin
        );

        void configurePins() const;

        StatusLED idle() const;
};

#endif
