#include "resistor.h"

float Resistor::testResistor(uint8_t pins[3], uint8_t analogPin, float VCC)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    setPinValues(pins[0], LOW, pins[1], HIGH);
    delay(50);
    float voltage = readAnalogPin(analogPin, VCC);
    
    float fixingRvalue1 = 1000.0;
    float fixingRvalue2 = 1000.0;

    if (voltage <= 0.15) 
    {
        pinMode(pins[0], INPUT);
        pinMode(pins[2], OUTPUT);
        digitalWrite(pins[2], LOW);
        delay(50);
        fixingRvalue2 = 34000.0;
        voltage = readAnalogPin(analogPin, VCC);
    }
    if (voltage <= 0.02)
    {
        return 0.0;
    }
    float allResistance = (VCC * fixingRvalue2) / voltage;
    float resistorValue = allResistance - (fixingRvalue1 + fixingRvalue2);
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