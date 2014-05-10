#include <LiquidCrystal.h>
#include "PowerSense.h"

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
        _lcd.begin(16, 2);
    }
    
    
    void processPowerSense(PowerSense& powerSense, int line)
    {
        char output[64];
        memset(output, 0, sizeof(output));
        dtostrf(powerSense.getVolts(), 5, 2, output + strlen(output));
        strcat(output, "V ");
        dtostrf(powerSense.getCurrent(), 5, 2, output + strlen(output));
        strcat(output, "A               ");
        for (int x = 0; x < strlen(output); x++)
        {
            _lcd.setCursor(x, line);
            _lcd.write(output[x]);
        }
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
    LiquidCrystal _lcd;
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








