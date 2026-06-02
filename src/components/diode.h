#ifndef diode_H
#define diode_H

#include <Arduino.h>
#include "baseComponent.h"

enum diodeStatus
{
    DIODE_INSERTED_A_C,
    DIODE_INSERTED_C_A,
    DIODE_NOT_WORKING
};

class Diode : public baseComponent
{
    public:
        diodeStatus testDiode(uint8_t pins[2], uint8_t analogPin, float VCC, float tolerance = 0.2, float diodeForwardVoltage = 0.7);
        static const char* statusToText(diodeStatus status);
    private:
        void getVoltages(uint8_t analogPin, uint8_t pins[2], float VCC, float &voltageHighLow, float &voltageLowHigh);
};
#endif