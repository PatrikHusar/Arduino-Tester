#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t dPins[3], uint8_t aPins[3], float VCC, float tolerance)
{
    transistorStatus transistorType;
    Transistor::pinPos transistorElectrodesPos[3];
    setPinMode(dPins[0], OUTPUT, dPins[1], OUTPUT, dPins[2], OUTPUT);
    float v1[3], v2[3], v3[3];
    float pinSet1[3] = {HIGH, HIGH, LOW};
    float pinSet2[3] = {LOW, HIGH, HIGH};
    float pinSet3[3] = {HIGH, LOW, HIGH};
    measurePins(dPins, aPins, pinSet1, VCC, v1);
    measurePins(dPins, aPins, pinSet2, VCC, v2);
    measurePins(dPins, aPins, pinSet3, VCC, v3);
    float values[3][3];
    for (int i = 0; i < 3; ++i) {
        values[0][i] = v1[i];
        values[1][i] = v2[i];
        values[2][i] = v3[i];
    }
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
    if (npnMatches == 1)
    {
        transistorType = TRANSISTOR_INSERTED_NPN;
        transistorElectrodesPos[0].pin = dPins[npnBaseIndex];
        transistorElectrodesPos[0].name = "Base";

        uint8_t idx1 = (npnBaseIndex + 1) % 3;
        uint8_t idx2 = (npnBaseIndex + 2) % 3;

        setPinMode(dPins[idx1], OUTPUT, dPins[idx2], OUTPUT, dPins[npnBaseIndex], INPUT_PULLUP);
        setPinValues(dPins[idx1], HIGH, dPins[idx2], LOW);
        delay(50);
        float voltageAtIdx2 = readAnalogPin(aPins[npnBaseIndex], VCC);

        setPinValues(dPins[idx1], LOW, dPins[idx2], HIGH);
        delay(50);
        float voltageAtIdx1 = readAnalogPin(aPins[npnBaseIndex], VCC);
        if (voltageAtIdx1 < voltageAtIdx2)
        {
            transistorElectrodesPos[1].pin = dPins[idx1];
            transistorElectrodesPos[1].name = "Collector";
            transistorElectrodesPos[2].pin = dPins[idx2];
            transistorElectrodesPos[2].name = "Emitter";
        }
        else
        {
            transistorElectrodesPos[1].pin = dPins[idx2];
            transistorElectrodesPos[1].name = "Collector";
            transistorElectrodesPos[2].pin = dPins[idx1];
            transistorElectrodesPos[2].name = "Emitter";
        }
    }
    else if (pnpMatches == 1 && npnMatches != 1)
    {
        transistorType = TRANSISTOR_INSERTED_PNP;
        transistorElectrodesPos[0].pin = dPins[pnpBaseIndex];
        transistorElectrodesPos[0].name = "Base";

        uint8_t idx1 = (pnpBaseIndex + 1) % 3;
        uint8_t idx2 = (pnpBaseIndex + 2) % 3;

        setPinMode(dPins[idx2], OUTPUT, dPins[pnpBaseIndex], OUTPUT, dPins[idx1], INPUT_PULLUP);
        setPinValues(dPins[idx2], LOW, dPins[pnpBaseIndex], LOW);
        delay(100);
        float voltageAtIdx1 = readAnalogPin(aPins[idx1], VCC);

        setPinMode(dPins[idx1], OUTPUT, dPins[pnpBaseIndex], OUTPUT, dPins[idx2], INPUT_PULLUP);
        setPinValues(dPins[idx1], LOW, dPins[pnpBaseIndex], LOW);
        delay(100);
        float voltageAtIdx2 = readAnalogPin(aPins[idx2], VCC);

        if (voltageAtIdx1 < voltageAtIdx2) {
            transistorElectrodesPos[1].pin = dPins[idx1];
            transistorElectrodesPos[1].name = "Emitter";
            transistorElectrodesPos[2].pin = dPins[idx2];
            transistorElectrodesPos[2].name = "Collector";
        } else {
            transistorElectrodesPos[1].pin = dPins[idx2];
            transistorElectrodesPos[1].name = "Emitter";
            transistorElectrodesPos[2].pin = dPins[idx1];
            transistorElectrodesPos[2].name = "Collector";
        }
    }
    else if (npnMatches == 3)
    {
        transistorType = TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        transistorType = TRANSISTOR_NOT_WORKING;
    }

    Serial.println(transistorElectrodesPos[0].name + ": " + String(transistorElectrodesPos[0].pin) + ", " +
                    transistorElectrodesPos[1].name + ": " + String(transistorElectrodesPos[1].pin) + ", " +
                    transistorElectrodesPos[2].name + ": " + String(transistorElectrodesPos[2].pin));

    return transistorType;
}

void Transistor::measurePins(uint8_t dPins[3], uint8_t aPins[3], float pinValues[3], float VCC, float voltages[3])
{
    setPinValues(dPins[0], pinValues[0], dPins[1], pinValues[1], dPins[2], pinValues[2]);
    delay(50);
    voltages[0] = readAnalogPin(aPins[0], VCC);
    voltages[1] = readAnalogPin(aPins[1], VCC);
    voltages[2] = readAnalogPin(aPins[2], VCC);
}
