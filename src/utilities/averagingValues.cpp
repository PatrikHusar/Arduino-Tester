#include "averagingValues.h"

float AveragingValues::createAverage(float value)
{
    values[i] = value;
    i++;
    for (int j = 0; j < size; j++)
    {
        average += values[j];
    }
    average = average / size;
    if (i >= size)
    {
        i = 0;
    }
    Serial.println(average);
    return average;
}

AveragingValues::AveragingValues(int nSize)
{
    i = 0;
    size = nSize;
    for (int j = 0; j < size; j++)
    {
        values[j] = 0.0;
    }
}
