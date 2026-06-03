#include "diode.h"

diodeStatus Diode::testDiode(uint8_t pins[2], uint8_t analogPin, float VCC, float &diodeForwardVoltage, float tolerance)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPin, pins, VCC, voltageHighLow, voltageLowHigh);
    diodeForwardVoltage = getOpenDiodeForwardVoltage(voltageHighLow, voltageLowHigh, VCC);
    if ((voltageHighLow > diodeForwardVoltage - tolerance) &&
        (voltageHighLow < diodeForwardVoltage + tolerance) &&
        (voltageLowHigh > 0 - smallValue) &&
        (voltageLowHigh < 0 + smallValue))
    {
        return DIODE_INSERTED_A_C;
    }
    else if ((voltageHighLow > VCC - smallValue) &&
            (voltageHighLow < VCC + smallValue) &&
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

float Diode::getOpenDiodeForwardVoltage(float voltageHighLow, float voltageLowHigh, float VCC)
{
    if (voltageHighLow > VCC - smallValue &&
        voltageHighLow < VCC + smallValue &&
        voltageLowHigh > 0 - smallValue &&
        voltageLowHigh < 0 + smallValue)
    {
        return 0.00;
    }
    else if (voltageHighLow > VCC - smallValue &&
             voltageHighLow < VCC + smallValue)
    {
        return VCC - voltageLowHigh;
    }
    else if (voltageHighLow > voltageLowHigh)
    {
        return voltageHighLow;
    }
    return 0.00;
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
    case DIODE_INSERTED_A_C: return "A-C";
    case DIODE_INSERTED_C_A: return "C-A";
    case DIODE_NOT_WORKING:  return "not working";
    default:                 return "unknown status";
  }
}