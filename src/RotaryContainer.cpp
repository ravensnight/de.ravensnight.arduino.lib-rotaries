
#include <Arduino.h>
#include <PinChangeInterrupt.h>
#include <RotaryContainer.h>

RotaryContainer::RotaryContainer() {
    this->_size = 0x00;
    this->_ready = false;
}

void RotaryContainer::pinChangedISR() {
    RotaryContainer::instance.update();
}

uint8_t RotaryContainer::add(uint8_t pinA, uint8_t pinB) {

    if (_size < MAX_ROTARY_COUNT) {
        this->_rotaries[this->_size].setup(pinA, pinB);
        this->_size++;

        return _size;
    }

    return 0;
}

Rotary* RotaryContainer::get(uint8_t idx) {
    if ((idx >= 0) && (idx < this->_size)) {
        return &(this->_rotaries[idx]);
    }

    return 0;
}

void RotaryContainer::install() {
    for (uint8_t i = 0; i < this->_size; i++) {
        Rotary& r = this->_rotaries[i];

        pinMode(r.pinA(), INPUT_PULLUP);
        pinMode(r.pinB(), INPUT_PULLUP);
        
        attachPCINT(digitalPinToPCINT(r.pinA()), RotaryContainer::pinChangedISR, CHANGE);
        attachPCINT(digitalPinToPCINT(r.pinB()), RotaryContainer::pinChangedISR, CHANGE);
    }
}

void RotaryContainer::update() {
    for (uint8_t i = 0; i < this->_size; i++) {
        Rotary& r = this->_rotaries[i];
        r.update();
    }
}

uint8_t RotaryContainer::size() {
    return _size;
}

uint8_t RotaryContainer::dirtyMask() {
    uint8_t mask = 0;
    for (uint8_t i = 0; i < this->_size; i++) {
        Rotary r = this->_rotaries[i];
        if (r.isDirty()) {
            mask |= (1 << i);
        }
    }

    return mask;
}

void RotaryContainer::reset() {
    for (uint8_t i = 0; i < this->_size; i++) {
        Rotary r = this->_rotaries[i];
        r.value(0x00);
    }
}

RotaryContainer RotaryContainer::instance = RotaryContainer();