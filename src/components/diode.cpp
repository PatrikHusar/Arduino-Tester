#include "diode.h"

DiodeStatus Diode::testDiode(uint8_t digiPin1, uint8_t digiPin2, uint8_t analogPin, float VCC, float tolerance, float diodeForwardVoltage)
{
    setPinMode(digiPin1, OUTPUT, digiPin2, OUTPUT);
    float voltageHighLow, voltageLowHigh;
    getVoltages(analogPin, digiPin1, digiPin2, VCC, voltageHighLow, voltageLowHigh);
    Serial.println("meas: " + String(voltageHighLow) + ", " + String(voltageLowHigh));
    Serial.println("tolerance: " + String(tolerance) + ", forward voltage: " + String(diodeForwardVoltage));
    Serial.println("vcc: " + String(VCC));
    if (voltageHighLow == VCC &&
        voltageLowHigh == 0)
    {
        // diode not inserted
        return DIODE_NOT_INSERTED;
    }
    else if (voltageHighLow > diodeForwardVoltage - tolerance &&
            voltageHighLow < diodeForwardVoltage + tolerance &&
            voltageLowHigh == 0)
    {
        // diode inserted in anode-cathode direction
        return DIODE_INSERTED_A_C;
    }
    else if ((voltageHighLow == VCC) &&
            (voltageLowHigh > VCC - diodeForwardVoltage - tolerance) &&
            (voltageLowHigh < VCC - diodeForwardVoltage + tolerance))
    {
        // diode inserted in cathode-anode direction
        return DIODE_INSERTED_C_A;
    }
    // else if (voltageHighLow == 0 &&
    //         voltageLowHigh == VCC)
    // {
    //     // short circuited
    //     return SHORT_CIRCUITED;
    // }
    return DIODE_NOT_WORKING;
}

void Diode::getVoltages(uint8_t analogPin, uint8_t digiPin1, uint8_t digiPin2, float VCC, float &voltageHighLow, float &voltageLowHigh)
{
    setPinValues(digiPin1, HIGH, digiPin2, LOW);
    delay(50);
    voltageHighLow = readAnalogPin(analogPin, VCC);
    setPinValues(digiPin1, LOW, digiPin2, HIGH);
    delay(50);
    voltageLowHigh = readAnalogPin(analogPin, VCC);
}
