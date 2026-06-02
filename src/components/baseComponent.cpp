#include "baseComponent.h"
#include "transistor.h"
#include "diode.h"
#include "resistor.h"

void baseComponent::testComponent(uint8_t mode, String &text1, String &text2, 
                                  void* transistorPtr, void* diodePtr, void* resistorPtr,
                                  uint8_t pins[], uint8_t analogPins[], float vcc)
{
  Transistor& transistor = *(Transistor*)transistorPtr;
  Diode& diode = *(Diode*)diodePtr;
  Resistor& resistor = *(Resistor*)resistorPtr;
  switch (mode)
  {
    case 0: {
      Transistor::pinPos transistorElectrodesPos[3];
      transistorStatus tStatus = transistor.testTransistor(pins, analogPins, vcc, transistorElectrodesPos);
      text1 = "type: " + String(Transistor::statusToText(tStatus));
      text2 = "pins: " + String(transistorElectrodesPos[0].name) + " : " 
                        + String(transistorElectrodesPos[1].name) + " : " 
                        + String(transistorElectrodesPos[2].name);
      break;
    }
    case 1: {
      diodeStatus dStatus = diode.testDiode(pins[0], pins[3], analogPins[0], vcc);
      text1 = "type: " + String(Diode::statusToText(dStatus));
      text2 = "";
      break;
    }
    case 2: {
      float resistorValue = resistor.testResistor(pins, analogPins[0], vcc, 1000.0);
      text1 = "resistance: ";
      text2 = resistor.formatResistorValue(resistorValue);
      break;
    }
  }
}

const char* baseComponent::modeToStr(uint8_t mode) {
  switch (mode) {
    case 0:  return "Testing Transistor";
    case 1:  return "Testing Diode";
    case 2:  return "Testing Resistor";
    default: return "unknown status";
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
float baseComponent::readAnalogPin(uint8_t pin, uint8_t vcc, float conversionFactor)
{
    return analogRead(pin) * (vcc / conversionFactor);
}