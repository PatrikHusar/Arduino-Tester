#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <Arduino.h>

class baseComponent
{
public:
    static const char* modeToStr(uint8_t mode);
    static const char* componentAllowedPins(uint8_t mode);
    static void setPinMode(uint8_t pin1, uint8_t mode1, uint8_t pin2 = 255, uint8_t mode2 = 255, uint8_t pin3 = 255, uint8_t mode3 = 255);
    static void setPinValues(uint8_t pin1, uint8_t value1, uint8_t pin2 = 255, uint8_t value2 = 255, uint8_t pin3 = 255, uint8_t value3 = 255);
    static float readAnalogPin(uint8_t pin, uint8_t vcc, float conversionFactor = 1023.0);
    static void testComponent(uint8_t mode, String &text1, String &text2, 
                              void* transistorPtr, void* diodePtr, void* resistorPtr,
                              uint8_t pins[], uint8_t analogPins[], float vcc);
private:
};

#endif