#include "averagingValues.h"

AveragingValues::AveragingValues(float *nValues, int nSize)
{
    i = 0;
    size = nSize;
    values = nValues;
    for (int j = 0; j < size; j++)
    {
        values[j] = 0.0;
    }
}

float AveragingValues::createAverage(float value)
{
    values[i] = value;
    i++;
    average = 0.0; 
    for (int j = 0; j < size; j++)
    {
        average += values[j];
    }
    average = average / size;
    if (i >= size || filledValues == true)
    {
        if (i >= size)
        {
            i = 0;
        }
        filledValues = true;
        return average;
    }
    return value;
}