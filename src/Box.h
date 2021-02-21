#ifndef BOX_H
#define BOX_H

class Box {
    private:
        byte _lockPin;
        byte _statePin;

    public:
        Box(
            byte lockPin,
            byte statePin
        );

        bool isClosed() const;

        void unlock() const;

        void lock() const;
};

#endif
