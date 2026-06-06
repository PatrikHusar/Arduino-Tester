#ifndef resistor_H
#define resistor_H

#include <Arduino.h>
#include "baseComponent.h"
#include "../utilities/averagingValues.h"

class Resistor : public baseComponent
{
    public:
        static const int bufferSize = 20;
        float buffer[bufferSize];
        AveragingValues avg;
        float testResistor(uint8_t pins[2], uint8_t analogPin, float VCC, float resistor1Value);
        String formatResistorValue(float ohms);
};
#endif