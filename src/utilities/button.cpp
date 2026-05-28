#include "button.h"

void Button::init(uint8_t pin)
{
    buttonPin = pin;
    pinMode(buttonPin, INPUT_PULLUP);
}
void Button::checkPinButtonPressed(uint8_t &mode, uint8_t maxMode)
{
    if (millis() - lastPressedTime < 200)
    {
        return;
    }
    if (digitalRead(buttonPin) == LOW)
    {
        lastPressedTime = millis();
        mode += 1;
        if (mode > maxMode)
        {
            mode = 0;
        }
    }
}
