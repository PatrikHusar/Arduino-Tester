#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t emmiterPin, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    setPinMode(digiPin3, INPUT);
    DiodeStatus statusEmmiterPin1 = diode.testDiode(emmiterPin, digiPin1, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    setPinMode(digiPin1, INPUT);
    DiodeStatus statusEmmiterPin3 = diode.testDiode(emmiterPin, digiPin3, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    Serial.println("statusEmmiterPin2: " + String(statusEmmiterPin1) + ", statusEmmiterPin3: " + String(statusEmmiterPin3));
    if (statusEmmiterPin1 == DIODE_INSERTED_A_C &&
        statusEmmiterPin3 == DIODE_INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_NPN;
    }
    else if (statusEmmiterPin1 == DIODE_INSERTED_C_A &&
             statusEmmiterPin3 == DIODE_INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusEmmiterPin1 == DIODE_NOT_INSERTED &&
             statusEmmiterPin3 == DIODE_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        return TRANSISTOR_NOT_WORKING;
    }
}
