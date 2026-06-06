#include "resistor.h"

Resistor::Resistor() : avg(buffer, bufferSize)
{
}

float Resistor::testResistor(uint8_t pins[2], uint8_t analogPin, float VCC, float resistor1Value)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    setPinValues(pins[0], HIGH, pins[1], LOW);
    delay(50);
    float voltage = readAnalogPin(analogPin, VCC);
    float resistorValue = resistor1Value * (voltage / (VCC - voltage));    
    return avg.createAverage(resistorValue);
}

String Resistor::formatResistorValue(float ohms)
{
    String stringOhms;
    if (ohms >= 10000000.0)
    {
        stringOhms = "Too High";
    }
    else if (ohms >= 1000000.0)
    {
        float mohms = ohms / 1000000.0;
        stringOhms = String(mohms, 2) + " MOhm";
    }
    else if (ohms >= 1000.0) {
        float kohms = ohms / 1000.0;
        stringOhms = String(kohms, 1) + " kOhm";
    }
    else 
    {
        stringOhms = String(ohms, 0) + " Ohm";
    }
    return stringOhms;
}