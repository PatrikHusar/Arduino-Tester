#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    uint8_t basePin, baseAnalogPin, otherPin1, otherPin2, emmiterPin, collectorPin;
    findBasePinMain(digiPin1, digiPin2, digiPin3, analogPin1, analogPin2, analogPin3, VCC, tolerance, transistorTOpenVoltageDrop, basePin, baseAnalogPin, otherPin1, otherPin2);
    if (basePin == TRANSISTOR_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    transistorStatus transistorType = getTransistorType(otherPin1, otherPin2, basePin, baseAnalogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    if (transistorType == TRANSISTOR_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else if (transistorType == TRANSISTOR_NOT_WORKING)
    {
        return TRANSISTOR_NOT_WORKING;
    }
    else
    {
    findEmmiterAndCollector(digiPin1, digiPin2, digiPin3, basePin, baseAnalogPin, VCC, tolerance, transistorTOpenVoltageDrop, transistorType, emmiterPin, collectorPin);
    }
}

void Transistor::findBasePinMain(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance, float transistorTOpenVoltageDrop, uint8_t &basePin, uint8_t &baseAnalogPin, uint8_t &otherPin1, uint8_t &otherPin2)
{
    findBasePin(digiPin1, digiPin2, digiPin3, HIGH, LOW, LOW, analogPin1, analogPin2, analogPin3, VCC, tolerance, transistorTOpenVoltageDrop, basePin, baseAnalogPin, otherPin1, otherPin2);
    if (basePin == TRANSISTOR_NOT_INSERTED)
    {
        findBasePin(digiPin1, digiPin2, digiPin3, LOW, HIGH, LOW, analogPin1, analogPin2, analogPin3, VCC, tolerance, transistorTOpenVoltageDrop, basePin, baseAnalogPin, otherPin1, otherPin2);
        if (basePin == TRANSISTOR_NOT_INSERTED)
        findBasePin(digiPin1, digiPin2, digiPin3, LOW, LOW, HIGH, analogPin1, analogPin2, analogPin3, VCC, tolerance, transistorTOpenVoltageDrop, basePin, baseAnalogPin, otherPin1, otherPin2);
        {
            if (basePin == TRANSISTOR_NOT_INSERTED)
            {
                basePin = TRANSISTOR_NOT_INSERTED;
            }
        }
    }
}

void Transistor::findBasePin(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, bool pin1Value, bool pin2Value, bool pin3Value, uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance, float transistorTOpenVoltageDrop, uint8_t &basePin, uint8_t &baseAnalogPin, uint8_t &otherPin1, uint8_t &otherPin2)
{
    setPinMode(digiPin1, OUTPUT, digiPin2, OUTPUT, digiPin3, OUTPUT);
    setPinValues(digiPin1, pin1Value, digiPin2, pin2Value, digiPin3, pin3Value);
    delay(50);
    float voltage1 = readAnalogPin(analogPin1, VCC);
    float voltage2 = readAnalogPin(analogPin2, VCC);
    float voltage3 = readAnalogPin(analogPin3, VCC);
    Serial.println("voltages: " + String(voltage1) + ", " + String(voltage2) + ", " + String(voltage3));
    if (voltage1 > transistorTOpenVoltageDrop - tolerance &&
        voltage1 < transistorTOpenVoltageDrop + tolerance)
    {
        basePin = digiPin1;
        baseAnalogPin = analogPin1;
        otherPin1 = digiPin2;
        otherPin2 = digiPin3;
    }
    else if (voltage2 > transistorTOpenVoltageDrop - tolerance &&
            voltage2 < transistorTOpenVoltageDrop + tolerance)
    {
        basePin = digiPin2;
        baseAnalogPin = analogPin2;
        otherPin1 = digiPin1;
        otherPin2 = digiPin3;
    }
    else if (voltage3 > transistorTOpenVoltageDrop - tolerance &&
            voltage3 < transistorTOpenVoltageDrop + tolerance)
    {
        basePin = digiPin3;
        baseAnalogPin = analogPin3;
        otherPin1 = digiPin1;
        otherPin2 = digiPin2;
    }
    else
    {
    basePin = TRANSISTOR_NOT_INSERTED;
    }
    Serial.println("base pin: " + String(basePin));
    Serial.println("base analog pin: " + String(baseAnalogPin));
}

transistorStatus Transistor::getTransistorType(uint8_t otherPin1, uint8_t otherPin2, uint8_t basePin, uint8_t baseAnalogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    setPinMode(otherPin2, INPUT);
    DiodeStatus statusBasePin1 = diode.testDiode(basePin, otherPin1, baseAnalogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    setPinMode(otherPin1, INPUT);
    DiodeStatus statusBasePin2 = diode.testDiode(basePin, otherPin2, baseAnalogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    Serial.println("statusbasePin2: " + String(statusBasePin1) + ", statusbasePin3: " + String(statusBasePin2));
    if (statusBasePin1 == DIODE_INSERTED_A_C &&
        statusBasePin2 == DIODE_INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_NPN;
    }
    else if (statusBasePin1 == DIODE_INSERTED_C_A &&
             statusBasePin2 == DIODE_INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusBasePin1 == DIODE_NOT_INSERTED &&
             statusBasePin2 == DIODE_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        return TRANSISTOR_NOT_WORKING;
    }
}

void Transistor::findEmmiterAndCollector(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t basePin, uint8_t baseAnalogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop, transistorStatus transistorType, uint8_t &emmiterPin, uint8_t &collectorPin)
{
    
}