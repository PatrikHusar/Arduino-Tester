#ifndef transistor_H
#define transistor_H

#include <Arduino.h>
#include "diode.h"
#include "baseComponent.h"

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
    Diode diodeTester;
    uint8_t testIndex = 0;
    struct pinPos
    {
        int8_t pin = -1;
        String name = "";
    };
    static const char* statusToText(transistorStatus status);
    transistorStatus testTransistor(uint8_t dPins[3], uint8_t aPins[3], float VCC, Transistor::pinPos transistorElectrodesPos[3], float &openingU, float tolerance = 0.1);
    private:
        float getOpeningU(uint8_t basePin, uint8_t emitterPin, transistorStatus type, float VCC, uint8_t analogPinB, uint8_t analogPinE);
        void measurePins(uint8_t dPins[3], uint8_t aPins[3], float pinValues[3], float VCC, float voltages[3]);
        void sortElectrodesPos(Transistor::pinPos transistorElectrodesPos[3]);
        struct stepResult
        {
            uint8_t countHigh = 0;
            uint8_t countLow = 0;
            int8_t lowPinIndex = -1;
            bool isPinHigh[3] = {false, false, false};
        };
};
#endif