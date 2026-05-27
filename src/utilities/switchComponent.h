#include <Arduino.h>

class SwitchComponent
{
    public:
        uint8_t isPressed(uint8_t buttonPin, uint8_t maxMode);
        uint8_t mode = 0;
};