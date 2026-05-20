#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t emmiterPin, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    DiodeStatus statusPin1Emmiter = diode.testDiode(digiPin1, emmiterPin, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    DiodeStatus statusPin3Emmiter = diode.testDiode(digiPin3, emmiterPin, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    if (statusPin1Emmiter == INSERTED_A_C &&
        statusPin3Emmiter == INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusPin1Emmiter == INSERTED_C_A &&
             statusPin3Emmiter == INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_NPN;
    }
    else if (statusPin1Emmiter == EMPTY &&
             statusPin3Emmiter == EMPTY)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        return TRANSISTOR_NOT_WORKING;
    }






    setPinMode(digiPin1, OUTPUT, emmiterPin, OUTPUT, digiPin3, OUTPUT);
    setPinValues(digiPin1, HIGH, emmiterPin, LOW, digiPin3, LOW);
    delay(50);
    float voltageBase = readAnalogPin(analogPin, VCC);
    setPinValues(digiPin1, LOW, emmiterPin, HIGH, digiPin3, LOW);
    delay(50);
    float voltageCollector = readAnalogPin(analogPin, VCC);
    setPinValues(digiPin1, LOW, emmiterPin, LOW, digiPin3, HIGH);
    delay(50);
    float voltageEmitter = readAnalogPin(analogPin, VCC);
    Serial.println("voltages: " + String(voltageBase) + ", " + String(voltageCollector) + ", " + String(voltageEmitter));
    return TRANSISTOR_NOT_WORKING;
}
