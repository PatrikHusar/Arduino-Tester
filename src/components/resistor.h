#ifndef resistor_H
#define resistor_H

#include <Arduino.h>
#include "baseComponent.h"

class Resistor : public baseComponent
{
    public:
        float testResistor(uint8_t pins[2], uint8_t analogPin, float VCC, float resistor1Value);
        String formatResistorValue(float ohms);
};
#endif