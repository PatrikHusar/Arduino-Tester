#include "diode.h"

diodeStatus Diode::testDiode(uint8_t pin1, uint8_t pin2, uint8_t analogPin, float VCC, float tolerance, float diodeForwardVoltage)
{
    setPinMode(pin1, OUTPUT, pin2, OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPin, pin1, pin2, VCC, voltageHighLow, voltageLowHigh);
    if (voltageHighLow == VCC &&
        voltageLowHigh == 0)
    {
        return DIODE_NOT_INSERTED;
    }
    else if (voltageHighLow > diodeForwardVoltage - tolerance &&
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
    return DIODE_NOT_WORKING;
}

void Diode::getVoltages(uint8_t analogPin, uint8_t pin1, uint8_t pin2, float VCC, float &voltageHighLow, float &voltageLowHigh)
{
    setPinValues(pin1, HIGH, pin2, LOW);
    delay(50);
    voltageHighLow = readAnalogPin(analogPin, VCC);
    setPinValues(pin1, LOW, pin2, HIGH);
    delay(50);
    voltageLowHigh = readAnalogPin(analogPin, VCC);
}

const char* Diode::statusToText(diodeStatus status) {
  switch (status) {
    case DIODE_NOT_INSERTED: return "not inserted";
    case DIODE_INSERTED_A_C: return "A-C";
    case DIODE_INSERTED_C_A: return "C-A";
    case DIODE_NOT_WORKING:  return "not working";
    default:                 return "unknown status";
  }
}