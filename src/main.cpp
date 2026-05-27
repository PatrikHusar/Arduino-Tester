#include <Arduino.h>
#include <U8glib.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"

Diode diode;
Transistor transistor;
Resistor resistor;
uint8_t pins[3] = {2, 3, 4};
uint8_t analogPins[3] = {A2, A1, A0};
float VCC = 5.0;
U8GLIB_SSD1306_128X64 display;

const char* transistorStatusToText(transistorStatus status) {
  switch (status) {
    case TRANSISTOR_NOT_INSERTED:  return "not inserted";
    case TRANSISTOR_INSERTED_NPN:  return "type: NPN";
    case TRANSISTOR_INSERTED_PNP:  return "type: PNP";
    case TRANSISTOR_NOT_WORKING: return "not working";
    default: return "unknown status";}
}
const char* diodeStatusToText(diodeStatus status) {
  switch (status) {
    case DIODE_NOT_INSERTED: return "not inserted";
    case DIODE_INSERTED_A_C: return "inserted A-C";
    case DIODE_INSERTED_C_A: return "inserted C-A";
    case DIODE_NOT_WORKING: return "not working";
    default: return "unknown status";}
}

void setup()
{
  Serial.begin(9600);
  Serial.println("starting tester...");
}

void loop()
{
  String text = transistorStatusToText(transistor.testTransistor(pins, analogPins, VCC));
  display.firstPage();
  do
  {
    display.setFont(u8g_font_5x8);
    display.setPrintPos(1, 10);
    display.print("TRANSISTOR TESTING");
    display.setPrintPos(1, 30);
    display.print(text);
    display.setPrintPos(1, 50);
    // display.print("pins" + )
  // Serial.println(resistor.testResistor(2, 3, A0, VCC, 1000.0));
  // Serial.println(diode.testDiode(2, 3, A0, VCC));
  }
  while (display.nextPage());

  delay(1000);
}
