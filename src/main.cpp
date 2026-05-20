#include <Arduino.h>
#include "components/baseComponent.h"
#include "components/diode.h"

Diode diode; 

void setup()
{
  Serial.begin(9600);
  Serial.println("starting tester...");
}

void loop()
{
  Serial.println(diode.testDiode(2, 3, A0, 5.0));
  delay(1000);
}
