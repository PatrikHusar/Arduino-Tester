#ifndef averagingvalues_H
#define averagingvalues_H

#include <Arduino.h>

class AveragingValues
{
public:
    AveragingValues(float *values, int nSize);
    int i;
    int size;
    bool filledValues = false;
    float *values;
    float average = 0.0;
    float createAverage(float value);
};

#endif