#include "transistor.h"

transistorStatus Transistor::testTransistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance = 0.2, float transistorThreshold = 0.7)
{
    setPinMode(digiPin1, OUTPUT, digiPin2, OUTPUT, digiPin3, OUTPUT);
    setPinValues(digiPin1, HIGH, digiPin2, LOW, digiPin3, LOW);
    delay(50);
    float voltageBase = readAnalogPin(analogPin, VCC);
    setPinValues(digiPin1, LOW, digiPin2, HIGH, digiPin3, LOW);
    delay(50);
    float voltageCollector = readAnalogPin(analogPin, VCC);
    setPinValues(digiPin1, LOW, digiPin2, LOW, digiPin3, HIGH);
    delay(50);
    float voltageEmitter = readAnalogPin(analogPin, VCC);
    Serial.println("voltages: " + String(voltageBase) + ", " + String(voltageCollector) + ", " + String(voltageEmitter));
    return NOT_WORKING;
}
