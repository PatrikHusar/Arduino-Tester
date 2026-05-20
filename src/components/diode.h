#ifndef diode_H
#define diode_H

#include <Arduino.h>
#include "baseComponent.h"

enum DiodeStatus
{
    DIODE_NOT_INSERTED,
    DIODE_INSERTED_A_C,
    DIODE_INSERTED_C_A,
    DIODE_NOT_WORKING
};

class Diode : public baseComponent
{
    public:
        DiodeStatus testDiode(uint8_t digiPin1, uint8_t digiPin2, uint8_t analogPin, float VCC, float tolerance = 0.2, float diodeForwardVoltage = 0.7);
    private:
        void getVoltages(uint8_t analogPin, uint8_t digiPin1, uint8_t digiPin2, float VCC, float &voltageHighLow, float &voltageLowHigh);
};
#endif