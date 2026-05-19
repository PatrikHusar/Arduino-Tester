#include <Arduino.h>
#include "diode.h"

enum transistorStatus
{
    EMPTY,
    INSERTED_NPN,
    INSERTED_PNP,
    NOT_WORKING
};
class Transistor : public baseComponent
{
    public:
        transistorStatus testTransistor(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin, float VCC, float tolerance = 0.2, float transistorThreshold = 0.7);
};