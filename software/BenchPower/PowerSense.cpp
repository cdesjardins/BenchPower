/* 
    Copyright (C) 2014 Chris Desjardins - cjd@chrisd.info
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "PowerSense.h"
#include "Arduino.h"

#define AREF_5  5.0f
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
    float scaledPin = pin * (AREF_5 / 1023.0);
    return scaledPin;
}
float PowerSense::getVolts()
{
    int pin = readAvgPin(_voltsPin);
    float scaledPin = pin * (AREF_5 / 1023.0);
    /* Factor in the voltage divider on the 12v lines */
    scaledPin *= 2.5f;
    return scaledPin;
}

int compar(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int PowerSense::readAvgPin(int pin)
{
    // Read the analog pin 40 times.
    // Then sort all of those reads.
    // Then throw away the highest 10, and the lowest 10
    // Then average the remaining 20
    // to try to get a stable analog input
    int pins[10];
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