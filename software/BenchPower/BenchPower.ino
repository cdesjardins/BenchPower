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

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "UpsideLiquidCrystal.h"
#include "PowerSense.h"

// digital pins
#define BP_LCD_RS   12
#define BP_LCD_EN   11
#define BP_LCD_DB4  10
#define BP_LCD_DB5  9
#define BP_LCD_DB6  8
#define BP_LCD_DB7  7
// analog pins
#define BP_12V_REG_VOLTS    0
#define BP_12V_REG_AMPS     1
#define BP_12V_VOLTS        4
#define BP_12V_AMPS         5

class BenchPower
{
public:
    BenchPower()
    : _lcd(BP_LCD_RS, BP_LCD_EN, BP_LCD_DB4, BP_LCD_DB5, BP_LCD_DB6, BP_LCD_DB7),
      _powerSenseReg(BP_12V_REG_VOLTS, BP_12V_REG_AMPS),
      _powerSense(BP_12V_VOLTS, BP_12V_AMPS)
    {
        _lcd.mybegin(16, 2);
    }
    
    
    void processPowerSense(PowerSense& powerSense, int line)
    {
        char output[64];
        memset(output, 0, sizeof(output));
        dtostrf(powerSense.getVolts(), 5, 2, output + strlen(output));
        strcat(output, "V ");
        dtostrf(powerSense.getCurrent(), 5, 2, output + strlen(output));
        strcat(output, "                ");
        _lcd.writeStr(0, line, output);
    }
    
    void processPowerSense()
    {
        unsigned long t0 = millis();
        if ((t0 - _powerSenseTimeStamp) > 1000)
        {
            _powerSenseTimeStamp = t0;
            processPowerSense(_powerSenseReg, 0);
            processPowerSense(_powerSense, 1);
        }
    }
    
    void process()
    {
        processPowerSense();
    }
private:
    UpsideLiquidCrystal _lcd;
    PowerSense _powerSenseReg;
    PowerSense _powerSense;
    unsigned long _powerSenseTimeStamp;
};

BenchPower *g_benchPower;

void setup()
{
    g_benchPower = new BenchPower();
}
void loop()
{
    g_benchPower->process();
}








