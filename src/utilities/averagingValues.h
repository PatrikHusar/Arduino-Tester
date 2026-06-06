#ifndef averagingvalues_H
#define averagingvalues_H

#include <Arduino.h>

class AveragingValues
{
public:
    AveragingValues();
    
    unsigned long count;
    float average;

    float createAverage(float value);
    void reset();
};

#endif