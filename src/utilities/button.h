#ifndef button_H
#define button_H

#include <Arduino.h>

class Button
{
    public:
        uint8_t buttonPin;
        unsigned long lastPressedTime = 0;
        void init(uint8_t pin);
        void checkPinButtonPressed(uint8_t &mode, uint8_t maxMode);

};
#endif