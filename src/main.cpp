#include <Arduino.h>
#include <U8glib.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"
#include "utilities/button.h"
#include "utilities/display.h"

Button switchButton;
Button acceptButton;
Diode diode;
Transistor transistor;
Resistor resistor;
uint8_t pins[3] = {2, 3, 4};
uint8_t analogPins[3] = {A2, A1, A0};
uint8_t switchButtonPin = 13;
uint8_t acceptButtonPin = 12;
U8GLIB_SSD1306_128X64 display;
String text1;
String text2;
float VCC = 5.0;
uint8_t switchMode = 0;
uint8_t accept = 0;
unsigned long lastMeasuredTime = 0;
uint8_t lastSwitchMode = 0;

void testComponent(uint8_t mode, String &text1, String &text2)
{
  switch (mode)
  {
    case 0: 
    {
      Transistor::pinPos transistorElectrodesPos[3];
      transistorStatus tStatus = transistor.testTransistor(pins, analogPins, VCC, transistorElectrodesPos);
      text1 = "type: " + String(Transistor::statusToText(tStatus));
      text2 = "pins: " + String(transistorElectrodesPos[0].name) + " : " 
                        + String(transistorElectrodesPos[1].name) + " : " 
                        + String(transistorElectrodesPos[2].name);
      break;
    }
    case 1: 
    {
      diodeStatus dStatus = diode.testDiode(pins, analogPins[0], VCC);
      text1 = "type: " + String(Diode::statusToText(dStatus));
      text2 = "";
      break;
    }
    case 2: 
    {
      float resistorValue = resistor.testResistor(pins, analogPins[0], VCC, 1000.0);
      text1 = "resistance: ";
      text2 = resistor.formatResistorValue(resistorValue);
      break;
    }
    default: 
      text1 = "unknown mode";
      text2 = "";
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  switchButton.init(switchButtonPin);
  acceptButton.init(acceptButtonPin);
}
void loop()
{
  switchButton.checkPinButtonPressed(switchMode, 2);
  if (switchMode != lastSwitchMode)
  {
    lastSwitchMode = switchMode;
    accept = 0;
    Display::displayText("", "", switchMode, display);
  }
  acceptButton.checkPinButtonPressed(accept, 1);
  if (accept == 1)
  {
    if (millis() - lastMeasuredTime > 1000)
    {
      lastMeasuredTime = millis();
      testComponent(switchMode, text1, text2);
      Display::displayText(text1, text2, switchMode, display);
    }
  }
  else
  {
    accept = 0;
  }
}
