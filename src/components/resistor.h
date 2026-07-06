#ifndef resistor_H
#define resistor_H

#include <Arduino.h>
#include "baseComponent.h"
#include "../utilities/averagingValues.h"

class Resistor : public baseComponent
{
    public:
        static const int bufferSize = 40;
        float buffer[bufferSize];
        AveragingValues avg;
        float testResistor(uint8_t pins[3], uint8_t analogPin, float VCC);
        String formatResistorValue(float ohms);
};
#endif