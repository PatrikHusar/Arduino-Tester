#include "switchComponent.h"

uint8_t SwitchComponent::isPressed(uint8_t buttonPin, uint8_t maxMode) {
    pinMode(buttonPin, INPUT_PULLUP);
    if (digitalRead(buttonPin) == LOW)
    {
        mode += 1;
        if (mode > maxMode)
        {
            mode = 0;
        }
    }
    return mode;
}