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