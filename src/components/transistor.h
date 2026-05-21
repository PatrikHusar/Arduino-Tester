#ifndef transistor_H
#define transistor_H

#include <Arduino.h>
#include "diode.h"

enum transistorStatus
{
    TRANSISTOR_NOT_INSERTED,
    TRANSISTOR_INSERTED_NPN,
    TRANSISTOR_INSERTED_PNP,
    TRANSISTOR_NOT_WORKING
};
class Transistor : public baseComponent
{
    public:
        transistorStatus testTransistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance = 0.2, float transistorTOpenVoltageDrop = 0.7);
};
#endif