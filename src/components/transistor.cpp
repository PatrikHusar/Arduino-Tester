#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t basePin, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop)
{
    Diode diode;
    setPinMode(digiPin3, INPUT);
    DiodeStatus statusbasePin1 = diode.testDiode(basePin, digiPin1, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    setPinMode(digiPin1, INPUT);
    DiodeStatus statusbasePin3 = diode.testDiode(basePin, digiPin3, analogPin, VCC, tolerance, transistorTOpenVoltageDrop);
    Serial.println("statusbasePin2: " + String(statusbasePin1) + ", statusbasePin3: " + String(statusbasePin3));
    if (statusbasePin1 == DIODE_INSERTED_A_C &&
        statusbasePin3 == DIODE_INSERTED_A_C)
    {
        return TRANSISTOR_INSERTED_NPN;
    }
    else if (statusbasePin1 == DIODE_INSERTED_C_A &&
             statusbasePin3 == DIODE_INSERTED_C_A)
    {
        return TRANSISTOR_INSERTED_PNP;
    }
    else if (statusbasePin1 == DIODE_NOT_INSERTED &&
             statusbasePin3 == DIODE_NOT_INSERTED)
    {
        return TRANSISTOR_NOT_INSERTED;
    }
    else
    {
        return TRANSISTOR_NOT_WORKING;
    }
}
