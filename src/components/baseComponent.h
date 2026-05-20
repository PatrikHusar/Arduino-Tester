#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <Arduino.h>

class baseComponent
{
public:
    void setPinMode(uint8_t pin1, uint8_t mode1, uint8_t pin2 = 255, uint8_t mode2 = 255, uint8_t pin3 = 255, uint8_t mode3 = 255);
    void setPinValues(uint8_t pin1, uint8_t value1, uint8_t pin2 = 255, uint8_t value2 = 255, uint8_t pin3 = 255, uint8_t value3 = 255);
    float readAnalogPin(uint8_t pin, uint8_t vcc, float conversionFactor = 1023.0);
private:
};

#endif