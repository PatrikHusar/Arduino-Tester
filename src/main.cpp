#include <Arduino.h>
#include <U8glib.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"
#include "utilities/switchComponent.h"

Diode diode;
Transistor transistor;
Resistor resistor;
SwitchComponent switchComponent;
uint8_t pins[3] = {2, 3, 4};
uint8_t analogPins[3] = {A2, A1, A0};
float VCC = 5.0;
uint8_t buttonPin = 13;
U8GLIB_SSD1306_128X64 display;

const char* modeToStr(uint8_t mode) {
  switch (mode) {
    case 0:  return "Testing Transistor";
    case 1:  return "Testing Diode";
    case 2:  return "Testing Resistor";
    default: return "unknown status";
  }
}

Transistor::pinPos transistorElectrodesPos[3];

void setup()
{
  Serial.begin(9600);
  Serial.println("starting tester...");
}

String text1;
String text2;
void loop()
{
  delay(1000);
  display.firstPage();
  do
  {
    uint8_t mode = switchComponent.isPressed(buttonPin, 2);
    display.setFont(u8g_font_5x8);
    display.setPrintPos(1, 10);
    display.print(modeToStr(mode));
    if (mode == 0) 
    {
    text1 = "type: " + String(Transistor::statusToText(transistor.testTransistor(pins, analogPins, VCC, transistorElectrodesPos)));
    text2 = "pins: " + String(transistorElectrodesPos[0].name) + " : " + String(transistorElectrodesPos[1].name) + " : " + String(transistorElectrodesPos[2].name);
    }
    else if (mode == 1)
    {
      text1 = "type: " + String(Diode::statusToText(diode.testDiode(pins, analogPins[0], VCC)));
    }
    else if (mode == 2)
    {
      float resistorValue = resistor.testResistor(pins, analogPins[0], VCC, 1000.0);
      text1 = "resistance: " + String(resistorValue) + " Ohms";
    }
    display.setPrintPos(1, 30);
    display.print(text1);
    if (mode == 0)
    {
      display.setPrintPos(1, 50);
      display.print(text2);
    }
  // Serial.println(resistor.testResistor(2, 3, A0, VCC, 1000.0));
  }
  while (display.nextPage());

  // Serial.println(resistor.testResistor(pins, A0, 5.0, 1000.0));
  Serial.println(transistor.testTransistor(pins, analogPins, 5.0, transistorElectrodesPos));
  // Serial.println(diode.testDiode(pins, A0, 5.0));
}
