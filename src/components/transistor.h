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
        transistorStatus testTransistor(uint8_t digiPin1, uint8_t basePin, uint8_t digiPin3, uint8_t analogPin, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance = 0.2, float transistorTOpenVoltageDrop = 0.7);
    private:
        void findBasePin(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, bool pin1Value, bool pin2Value, bool pin3Value, uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance, float transistorTOpenVoltageDrop, uint8_t &basePin, uint8_t &baseAnalogPin, uint8_t &emmiterPin, uint8_t &collectorPin);
        void findBasePinMain(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t analogPin1, uint8_t analogPin2, uint8_t analogPin3, float VCC, float tolerance, float transistorTOpenVoltageDrop, uint8_t &basePin, uint8_t &baseAnalogPin, uint8_t &otherPin1, uint8_t &otherPin2);
        transistorStatus getTransistorType(uint8_t otherPin1, uint8_t otherPin2, uint8_t basePin, uint8_t baseAnalogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop);
        void findEmmiterAndCollector(uint8_t digiPin1, uint8_t digiPin2, uint8_t digiPin3, uint8_t basePin, uint8_t baseAnalogPin, float VCC, float tolerance, float transistorTOpenVoltageDrop, transistorStatus transistorType, uint8_t &emmiterPin, uint8_t &collectorPin);
};
#endif