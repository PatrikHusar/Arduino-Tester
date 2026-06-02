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
uint8_t pins[4] = {2, 3, 4, 5};
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

void setup()
{
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
      baseComponent::testComponent(switchMode, text1, text2, &transistor, &diode, &resistor, pins, analogPins, VCC);
      Display::displayText(text1, text2, switchMode, display);
    }
  }
  else
  {
    accept = 0;
  }
}
