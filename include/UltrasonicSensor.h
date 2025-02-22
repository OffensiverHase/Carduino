#ifndef DistanceSensor_h
#define DistanceSensor_h

class UltrasonicSensor {
    public:
        UltrasonicSensor(int trigPin, int echoPin);
        int getDistance();
    private:
        int trigPin;
        int echoPin;
};

#endif