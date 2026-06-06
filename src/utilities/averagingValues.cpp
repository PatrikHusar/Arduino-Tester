#include "averagingValues.h"

AveragingValues::AveragingValues()
{
    reset();
}

void AveragingValues::reset()
{
    count = 0;
    average = 0.0;
}

float AveragingValues::createAverage(float value)
{
    if (isinf(value))
    {
        reset();
        return value;
    }
    if (count > 0)
    {
        float difference = abs(value - average);
        float tolerance = average * 0.1;
        if (difference > tolerance)
        {
            reset();
        }
    }
    count++;
    average = average + ((value - average) / count);
    return average;
}
