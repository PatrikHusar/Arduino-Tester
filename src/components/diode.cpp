#include "diode.h"

diodeStatus Diode::testDiode(uint8_t pins[2], uint8_t analogPin, float VCC, float tolerance, float diodeForwardVoltage)
{
    setPinMode(pins[0], OUTPUT, pins[1], OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPin, pins, VCC, voltageHighLow, voltageLowHigh);
    Serial.println("meas: " + String(voltageHighLow) + ", " + String(voltageLowHigh));
    Serial.println("tolerance: " + String(tolerance) + ", forward voltage: " + String(diodeForwardVoltage));
    Serial.println("vcc: " + String(VCC));
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

void Diode::getVoltages(uint8_t analogPin, uint8_t pins[2], float VCC, float &voltageHighLow, float &voltageLowHigh)
{
    setPinValues(pins[0], HIGH, pins[1], LOW);
    delay(50);
    voltageHighLow = readAnalogPin(analogPin, VCC);
    setPinValues(pins[0], LOW, pins[1], HIGH);
    delay(50);
    voltageLowHigh = readAnalogPin(analogPin, VCC);
}
