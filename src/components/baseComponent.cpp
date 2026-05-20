#include "baseComponent.h"

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