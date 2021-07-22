#ifndef STATUSLED_H
#define STATUSLED_H

#include <Arduino.h>

class StatusLED {
    private:
        byte _greenPin;

        byte _redPin;

        byte _bluePin;

        const uint8_t _greenChannel = 0;
        const uint8_t _redChannel = 1;
        const uint8_t _blueChannel = 2;

        void greenOn() const;

        void greenOff() const;

        void redOn() const;

        void redOff() const;

        void blueOn() const;

        void blueOff() const;
    public:
        StatusLED(
            byte greenPin,
            byte redPin,
            byte bluePin
        );

        void configurePins() const;

        StatusLED idle() const;

        StatusLED flashGreen(unsigned short int times) const;

        StatusLED flashRed(unsigned short int times) const;
};

#endif
