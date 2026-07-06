#include "baseComponent.h"
#include "transistor.h"
#include "diode.h"
#include "resistor.h"

void baseComponent::testComponent(uint8_t mode, String &text1, String &text2, 
                                  void* transistorPtr, void* diodePtr, void* resistorPtr,
                                  uint8_t pins[], uint8_t analogPins[], float VCC, float fixedVCC)
{
    Transistor& transistor = *(Transistor*)transistorPtr;
    Diode& diode = *(Diode*)diodePtr;
    Resistor& resistor = *(Resistor*)resistorPtr;
    setPinMode(pins[3], INPUT);
    switch (mode)
    {
        case 0:
        {
            float openingU = 10.0;
            Transistor::pinPos transistorElectrodesPos[3];
            uint8_t dPins[3] = {pins[0], pins[1], pins[2]};
            transistorStatus tStatus = transistor.testTransistor(dPins, analogPins, fixedVCC, transistorElectrodesPos, openingU);
            text1 = "type: " + String(Transistor::statusToText(tStatus));
            if (openingU != 10.0)
            {
                text2 = "opening U: " + String(openingU) + " V";
            }
            else
            {
            text2 = "pins: " + String(transistorElectrodesPos[0].name) + " : " 
                                + String(transistorElectrodesPos[1].name) + " : " 
                                + String(transistorElectrodesPos[2].name);
            }
            break;
        }
        case 1:
        {
            uint8_t dPins[2] = {pins[0], pins[2]};
            uint8_t aPins[2] = {analogPins[0], analogPins[2]};
            float diodeForwardVoltage;
            diodeStatus dStatus = diode.testDiode(dPins, aPins, fixedVCC, diodeForwardVoltage);
            text1 = "inserted: " + String(Diode::statusToText(dStatus));
            text2 = "opening U: " + String(diodeForwardVoltage) + " V";
            break;
        }
        case 2:
        {
            uint8_t dPins[3] = {pins[0], pins[2], pins[3]};
            float resistorValue = resistor.testResistor(dPins, analogPins[0], VCC);
            text1 = "resistance:";
            text2 = resistor.formatResistorValue(resistorValue);
            break;
        }
    }
}

const char* baseComponent::modeToStr(uint8_t mode)
{
  switch (mode) {
    case 0:  return "Transistor Test";
    case 1:  return "Diode Test";
    case 2:  return "Resistor Test";
    default: return "unknown";
  }
}

const char* baseComponent::componentAllowedPins(uint8_t mode)
{
    switch (mode) {
    case 0:  return "use pins: 1, 2, 3";
    case 1:  return "use pins: 1, 3";
    case 2:  return "use pins: 1, 3";
    default: return "unknown";
  }
}

void baseComponent::setPinMode(uint8_t pin1, uint8_t mode1, uint8_t pin2, uint8_t mode2, uint8_t pin3, uint8_t mode3)
{
    if (pin1 != 255) {
        pinMode(pin1, mode1);
    }
    if (pin2 != 255) {
        pinMode(pin2, mode2);
    }
    if (pin3 != 255) {
        pinMode(pin3, mode3);
    }
}

void baseComponent::setPinValues(uint8_t pin1, uint8_t value1, uint8_t pin2, uint8_t value2, uint8_t pin3, uint8_t value3)
{
    if (pin1 != 255) {
        digitalWrite(pin1, value1);
    }
    if (pin2 != 255) {
        digitalWrite(pin2, value2);
    }
    if (pin3 != 255) {
        digitalWrite(pin3, value3);
    }
}

float baseComponent::readAnalogPin(uint8_t pin, uint8_t VCC)
{
    return analogRead(pin) * (VCC / 4095.0);
}