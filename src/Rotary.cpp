
#include <Arduino.h>
#include <Rotary.h>

Rotary::Rotary() {    
    value(0);
}

void Rotary::setup(uint8_t pinA, uint8_t pinB) {
    _pinA = pinA;
    _pinB = pinB;
}

int16_t Rotary::value() {
    return this->_val;
}

int16_t Rotary::commit() {
    int16_t old = this->_val;
    this->_val = 0;
    return old;
}

boolean Rotary::isDirty() {
    return _val != 0;
}

void Rotary::increment() {
    if (this->_val < ROTARY_MAX_VALUE) {
        this->_val++;
    }
}

void Rotary::decrement() {
    if (this->_val > ROTARY_MIN_VALUE) {
        this->_val--;
    }
}

void Rotary::value(int16_t val) {
    this->_val = val;
}

uint8_t Rotary::pinA() {
    return this->_pinA;
}

uint8_t Rotary::pinB() {
    return this->_pinB;
}

void Rotary::update() {
    uint8_t current = (digitalRead(this->pinA()) << 1) | digitalRead(this->pinB());

    switch (this->_bitmask | current) {
        case 0b0010:
            // increment();
            break;

        case 0b1101:
            increment();        
            break;

        case 0b0111:
            decrement();
            break;

        case 0b1000:
            // decrement();
            break;

        default:        
            break;
    }

    this->_bitmask = (current << 2);    
}
