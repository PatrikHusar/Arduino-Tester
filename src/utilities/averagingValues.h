#ifndef averagingvalues_H
#define averagingvalues_H

#include <Arduino.h>

class AveragingValues
{
public:
    AveragingValues(int nSize);
    int i;
    int size;
    float *values;
    float average = 0.0;
    float createAverage(float value);
};

#endif