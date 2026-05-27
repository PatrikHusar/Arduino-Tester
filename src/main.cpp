#include <Arduino.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"

Diode diode;
Transistor transistor;
Resistor resistor;
uint8_t pins[3] = {2, 3, 4};
uint8_t analogPins[3] = {A2, A1, A0};
Transistor::pinPos transistorElectrodesPos[3];

void setup()
{
  Serial.begin(9600);
  Serial.println("starting tester...");
}

void loop()
{
  // Serial.println(resistor.testResistor(pins, A0, 5.0, 1000.0));
  Serial.println(transistor.testTransistor(pins, analogPins, 5.0, transistorElectrodesPos));
  // Serial.println(diode.testDiode(pins, A0, 5.0));
  delay(1000);
}
