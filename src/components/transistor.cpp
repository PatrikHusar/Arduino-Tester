#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t emmiterPin, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    DiodeStatus statusPin1Emmiter = diode.testDiode(digiPin1, emmiterPin, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    DiodeStatus statusPin3Emmiter = diode.testDiode(digiPin3, emmiterPin, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    if (statusPin1Emmiter == DIODE_INSERTED_A_C &&
        statusPin3Emmiter == DIODE_INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusPin1Emmiter == DIODE_INSERTED_C_A &&
             statusPin3Emmiter == DIODE_INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_NPN;
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
