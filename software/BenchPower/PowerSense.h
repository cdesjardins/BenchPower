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


#ifndef BP_POWER_SENSE_Hxx
#define BP_POWER_SENSE_Hxx

class PowerSense
{
public:
    PowerSense(int voltsPin, int currentPin);
    float getCurrent();
    float getVolts();
protected:
    int readAvgPin(int pin);

private:
    int _voltsPin;
    int _currentPin;
};

#endif