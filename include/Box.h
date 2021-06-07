#ifndef BOX_H
#define BOX_H

#include <BoxAuthorizer.h>

class Box {
    private:
        byte _lockPin;

        byte _statePin;

        BoxAuthorizer _authorizer;

    public:
        Box(
            byte lockPin,
            byte statePin,
            BoxAuthorizer& authorizer
        );

        void configurePins() const;

        bool isOpened() const;

        void unlock() const;

        void lock() const;
};

#endif
