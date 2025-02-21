#ifndef DistanceSensor_h
#define DistanceSensor_h

class DistanceSensor {
    public:
        DistanceSensor(int trigPin, int echoPin);
        int getDistance();
    private:
        int trigPin;
        int echoPin;
};

#endif