#include <Arduino.h>
#include <U8glib.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"
#include "utilities/button.h"

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
      text1 = "resistance: " + String(resistorValue) + " Ohms";
      text2 = "";
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
  Serial.println("Starting Tester.");
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
    display.firstPage();
    do
    {
      display.setFont(u8g_font_7x13);
      display.setPrintPos(1, 10);
      display.print(baseComponent::modeToStr(switchMode));
    }
    while (display.nextPage());
  }
  acceptButton.checkPinButtonPressed(accept, 1);
  if (accept == 1)
  {
    if (millis() - lastMeasuredTime > 1000)
    {
      lastMeasuredTime = millis();
      testComponent(switchMode, text1, text2);
      display.firstPage();
      do
      {
        display.setFont(u8g_font_7x13);
        display.setPrintPos(1, 10);
        display.print(baseComponent::modeToStr(switchMode));
        display.setPrintPos(1, 30);
        display.print(text1);
        display.setPrintPos(1, 50);
        display.print(text2);
      }
      while (display.nextPage());
    }
  }
  else
  {
    accept = 0;
  }
}
