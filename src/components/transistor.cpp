#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t emmiterPin, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    setPinMode(digiPin3, INPUT);
    DiodeStatus statusPin1Emmiter = diode.testDiode(emmiterPin, digiPin1, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    setPinMode(digiPin1, INPUT);
    DiodeStatus statusPin3Emmiter = diode.testDiode(emmiterPin, digiPin3, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    Serial.println("statusPin1Emmiter: " + String(statusPin1Emmiter) + ", statusPin3Emmiter: " + String(statusPin3Emmiter));
    if (statusPin1Emmiter == DIODE_INSERTED_A_C &&
        statusPin3Emmiter == DIODE_INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_NPN;
    }
    else if (statusPin1Emmiter == DIODE_INSERTED_C_A &&
             statusPin3Emmiter == DIODE_INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusPin1Emmiter == DIODE_NOT_INSERTED &&
             statusPin3Emmiter == DIODE_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        return TRANSISTOR_NOT_WORKING;
    }
}
