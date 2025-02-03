#ifndef __ROTARY_H__
#define __ROTARY_H__

#include <Arduino.h>
#include <Stream.h>

#define ROTARY_MAX_VALUE 32767
#define ROTARY_MIN_VALUE -32767

class Rotary {

    private:
        volatile int16_t _val = 0;        
        volatile uint8_t _bitmask = 0;
        uint8_t _pinA = 1;
        uint8_t _pinB = 2;

    public:

        Rotary();

        void setup(uint8_t pinA, uint8_t pinB);

        int16_t value();
        void value(int16_t val);

        void increment();        
        void decrement();

        /**
         * Read pins and update the internal state mask
         * Return true, if bitmask changed.
         */
        void update();        

        /**
         * Store the last value as the one received via I2C
         */
        int16_t commit();

        /**
         * Return true, if value differs from committed.
         */
        boolean isDirty();

        uint8_t pinA();
        uint8_t pinB();
};

#endif // __ROTARY_H__