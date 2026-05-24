#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3,
                                            uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3,
                                            float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    uint8_t basePin, baseAnalogPin, otherPin1, otherPin2, emmiterPin, collectorPin;
    transistorStatus transistorType;
    findBaseAndGetTransistorType(digiPin1, digiPin2, digiPin3,
                                analogPin1, analogPin2, analogPin3,
                                VCC, tolerance, transistorTOpenVoltageDrop,
                                basePin, baseAnalogPin, otherPin1, otherPin2, transistorType);

    return TRANSISTOR_NOT_INSERTED;
}

void Transistor::findBaseAndGetTransistorType(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, 
                                              uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, 
                                              float VCC, float tolerance, float transistorTOpenVoltageDrop, 
                                              uint8_t &basePin, uint8_t &baseAnalogPin, 
                                              uint8_t &otherPin1, uint8_t &otherPin2, 
                                              transistorStatus &transistorType)
{
    setPinMode(digiPin1, OUTPUT, digiPin2, OUTPUT, digiPin3, OUTPUT);
    float v11, v12, v13;
    float v21, v22, v23;
    float v31, v32, v33;

    measurePins(digiPin1, digiPin2, digiPin3, HIGH, HIGH, LOW,  analogPin1, analogPin2, analogPin3, VCC, v11, v12, v13);
    measurePins(digiPin1, digiPin2, digiPin3, LOW,  HIGH, HIGH, analogPin1, analogPin2, analogPin3, VCC, v21, v22, v23);
    measurePins(digiPin1, digiPin2, digiPin3, HIGH, LOW,  HIGH, analogPin1, analogPin2, analogPin3, VCC, v31, v32, v33);

    uint8_t dPins[3] = {digiPin1, digiPin2, digiPin3};
    uint8_t aPins[3] = {analogPin1, analogPin2, analogPin3};
    float values[3][3] =
    {
        {v11, v12, v13},
        {v21, v22, v23},
        {v31, v32, v33}
    };

    stepResult stepResults[3];
    for (uint8_t row = 0; row < 3; row++)
    {
        for (uint8_t column = 0; column < 3; column++)
        {
            if (abs(values[row][column] - VCC) <= tolerance)
            {
                stepResults[row].countHigh++;
                stepResults[row].isPinHigh[column] = true;
            }
            else if (values[row][column] <= tolerance)
            {
                stepResults[row].countLow++;
                stepResults[row].lowPinIndex = column;
            }
        }
    }

    uint8_t npnMatches = 0;
    int8_t npnBaseIndex = -1;
    for (uint8_t row = 0; row < 3; row++)
    {
        if (stepResults[row].countHigh == 2 && stepResults[row].countLow == 1)
        {
            npnMatches++;
            npnBaseIndex = stepResults[row].lowPinIndex;
        }
    }

    uint8_t pnpMatches = 0;
    int8_t pnpBaseIndex = -1;
    for (uint8_t column = 0; column < 3; column++)
    {
        uint8_t highCountForPin = 0;
        if (stepResults[0].isPinHigh[column]) highCountForPin++;
        if (stepResults[1].isPinHigh[column]) highCountForPin++;
        if (stepResults[2].isPinHigh[column]) highCountForPin++;
        if (highCountForPin == 2)
        {
            pnpMatches++;
            pnpBaseIndex = column;
        }
    }

    if (npnMatches == 1 && pnpMatches == 0)
    {
        transistorType = TRANSISTOR_INSERTED_NPN;
        basePin = dPins[npnBaseIndex];
        baseAnalogPin = aPins[npnBaseIndex];
        otherPin1 = dPins[(npnBaseIndex + 1) % 3];
        otherPin2 = dPins[(npnBaseIndex + 2) % 3];
    }
    else if (pnpMatches == 1 && npnMatches == 2)
    {
        transistorType = TRANSISTOR_INSERTED_PNP;
        basePin = dPins[pnpBaseIndex];
        baseAnalogPin = aPins[pnpBaseIndex];
        otherPin1 = dPins[(pnpBaseIndex + 1) % 3];
        otherPin2 = dPins[(pnpBaseIndex + 2) % 3];
    }
    else
    {
        transistorType = TRANSISTOR_NOT_WORKING;
    }
}
void Transistor::measurePins(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3,
                            bool pin1Value, bool pin2Value, bool pin3Value,
                            uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3,
                            float VCC, float &voltage1, float &voltage2, float &voltage3)
{
    setPinValues(digiPin1, pin1Value, digiPin2, pin2Value, digiPin3, pin3Value);
    delay(50);
    voltage1 = readAnalogPin(analogPin1, VCC);
    voltage2 = readAnalogPin(analogPin2, VCC);
    voltage3 = readAnalogPin(analogPin3, VCC);
    Serial.println("voltages: " + String(voltage1) + ", " + String(voltage2) + ", " + String(voltage3));
    Serial.println("values: " + String(pin1Value) + ", " + String(pin2Value) + ", " + String(pin3Value));
}
void Transistor::findEmmiterAndCollector(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t basePin, uint8_t baseAnalogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop, transistorStatus transistorType, uint8_t &emmiterPin, uint8_t &collectorPin)
{
    
}