#include "resistor.h"

float Resistor::testResistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t analogPin, float VCC, float resistor1Value)
{
    setPinMode(digiPin1, OUTPUT, digiPin2, OUTPUT);
    setPinValues(digiPin1, HIGH, digiPin2, LOW);
    delay(50);
    float voltage = readAnalogPin(analogPin, VCC);
    return resistor1Value * (voltage / (VCC - voltage));
}