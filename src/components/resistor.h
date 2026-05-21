#ifndef resistor_H
#define resistor_H

#include <Arduino.h>
#include "baseComponent.h"

class Resistor : public baseComponent
{
    float testResistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t analogPin, float VCC, float resistor1Value);
};
#endif