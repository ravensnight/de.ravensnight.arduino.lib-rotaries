#ifndef __ROTARYCONTAINER_H__
#define __ROTARYCONTAINER_H__

#include <Arduino.h>
#include <Stream.h>
#include <Rotary.h>

#ifndef MAX_ROTARY_COUNT
    #define MAX_ROTARY_COUNT 6
#endif // MAX_ROTARY_COUNT


class RotaryContainer {

    private:

        volatile boolean _ready = false;  // global dirty flag
        volatile uint8_t _size = 0;

        Rotary _rotaries[MAX_ROTARY_COUNT];

        static void pinChangedISR();

        // Updates all Rotaries in a loop
        void update();        

        RotaryContainer();

    public:

        static RotaryContainer instance;

        uint8_t add(uint8_t pinA, uint8_t pinB);
        Rotary* get(uint8_t idx);

        // install all rotaries added
        void install();

        // Sets the dirty flag to 1
        uint8_t size();

        // return the dirty bit
        uint8_t dirtyMask();

        // reset all to 0.
        void reset();
};

#endif // __ROTARYCONTAINER_H__