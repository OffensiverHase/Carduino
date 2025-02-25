#ifndef ToFSensor_h
#define ToFSensor_h

#include <VL53L0X.h>

class ToFSensor {
    public:
        ToFSensor(int xShutPin, int i2cAddress);
        int getDistance();
    private:
        int xShutPin;
        VL53L0X sensor;
        int i2cAddress;
        
};

#endif