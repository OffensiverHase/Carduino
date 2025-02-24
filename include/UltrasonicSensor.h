#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

class UltrasonicSensor {
    public:
        UltrasonicSensor(int trigPin, int echoPin);
        int getDistance();
    private:
        int trigPin;
        int echoPin;
};

#endif