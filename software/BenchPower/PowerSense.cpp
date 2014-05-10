#include "PowerSense.h"
#include "Arduino.h"

#define VREF 5.21f
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
 
PowerSense::PowerSense(int voltsPin, int currentPin)
    :_voltsPin(voltsPin),
    _currentPin(currentPin)
{
    analogReference(DEFAULT);
}

float PowerSense::getCurrent()
{
    int pin = readAvgPin(_currentPin);
    float scaledPin = pin * (VREF / 1023.0);
    return scaledPin;
}
float PowerSense::getVolts()
{
    int pin = readAvgPin(_voltsPin);
    float scaledPin = pin * (VREF / 1023.0);
    float divider = 0.4f;
    float ret = scaledPin / divider;
    return ret;
}

int compar (const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int PowerSense::readAvgPin(int pin)
{
    int pins[40];
    for (int i = 0; i < ARRAY_SIZE(pins); i++)
    {
        pins[i] = analogRead(pin);
    }
    qsort(pins, ARRAY_SIZE(pins), sizeof(pins[0]), compar);
    int start = ARRAY_SIZE(pins) / 4;
    int end = ARRAY_SIZE(pins) - start;
    int total = 0;
    for (int i = start; i < end; i++)
    {
        total += pins[i];
    }
    total /= (end - start);
    return total;
}