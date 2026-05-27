#include "resistor.h"

float Resistor::testResistor(uint8_t pins[2], uint8_t analogPin, float VCC, float resistor1Value)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    setPinValues(pins[0], LOW, pins[1], HIGH);
    delay(50);
    float voltage = readAnalogPin(analogPin, VCC);
    return resistor1Value * (voltage / (VCC - voltage));
}