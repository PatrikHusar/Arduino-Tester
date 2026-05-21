#include <Arduino.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"

Diode diode;
Transistor transistor;
Resistor resistor;

void setup()
{
  Serial.begin(9600);
  Serial.println("starting tester...");
}

void loop()
{
  Serial.println(resistor.testResistor(2, 3, A0, 5.0, 1000.0));
  // Serial.println(transistor.testTransistor(2, 3, 4, A0, 5.0));
  // Serial.println(diode.testDiode(2, 3, A0, 5.0));
  delay(1000);
}
