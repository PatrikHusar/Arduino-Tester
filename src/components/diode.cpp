#include "diode.h"

diodeStatus Diode::testDiode(uint8_t pins[2], uint8_t analogPins[2], float VCC, float &diodeForwardVoltage, float tolerance)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPins, pins, VCC, voltageHighLow, voltageLowHigh);

    if (voltageHighLow < VCC - tolerance && voltageLowHigh > VCC - tolerance)
    {
        diodeForwardVoltage = (2.0 * voltageHighLow) - VCC;
        return DIODE_INSERTED_A_C;
    }
    else if (voltageHighLow > VCC - tolerance && voltageLowHigh < VCC - tolerance)
    {
        diodeForwardVoltage = (2.0 * voltageLowHigh) - VCC; 
        return DIODE_INSERTED_C_A;
    }
    else
    {
        diodeForwardVoltage = 0.0;
        return DIODE_NOT_WORKING;
    }
}

void Diode::getVoltages(uint8_t analogPins[2], uint8_t pins[2], float VCC, float &voltageHighLow, float &voltageLowHigh)
{
    setPinValues(pins[0], HIGH, pins[1], LOW);
    delay(50);
    voltageHighLow = readAnalogPin(analogPins[0], VCC);

    setPinValues(pins[0], LOW, pins[1], HIGH);
    delay(50);
    voltageLowHigh = readAnalogPin(analogPins[1], VCC);
}
const char* Diode::statusToText(diodeStatus status) {
  switch (status) {
    case DIODE_INSERTED_A_C: return "A-C";
    case DIODE_INSERTED_C_A: return "C-A";
    case DIODE_NOT_WORKING:  return "not working";
    default:                 return "unknown status";
  }
}