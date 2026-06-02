#include "diode.h"

diodeStatus Diode::testDiode(uint8_t pins[2], uint8_t analogPin, float VCC, float tolerance, float diodeForwardVoltage)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPin, pins, VCC, voltageHighLow, voltageLowHigh);
    if (voltageHighLow > diodeForwardVoltage - tolerance &&
        voltageHighLow < diodeForwardVoltage + tolerance &&
        voltageLowHigh == 0)
    {
        return DIODE_INSERTED_A_C;
    }
    else if ((voltageHighLow == VCC) &&
            (voltageLowHigh > VCC - diodeForwardVoltage - tolerance) &&
            (voltageLowHigh < VCC - diodeForwardVoltage + tolerance))
    {
        return DIODE_INSERTED_C_A;
    }
    else
    {
        return DIODE_NOT_WORKING;
    }
}

void Diode::getVoltages(uint8_t analogPin, uint8_t pins[2], float VCC, float &voltageHighLow, float &voltageLowHigh)
{
    setPinValues(pins[0], HIGH, pins[1], LOW);
    delay(50);
    voltageHighLow = readAnalogPin(analogPin, VCC);
    setPinValues(pins[0], LOW, pins[1], HIGH);
    delay(50);
    voltageLowHigh = readAnalogPin(analogPin, VCC);
}

const char* Diode::statusToText(diodeStatus status) {
  switch (status) {
    case DIODE_INSERTED_A_C: return "Aanode-Cathode";
    case DIODE_INSERTED_C_A: return "Cathode-Anode";
    case DIODE_NOT_WORKING:  return "not working";
    default:                 return "unknown status";
  }
}