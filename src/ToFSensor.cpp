#include <ToFSensor.h>

ToFSensor::ToFSensor(int xShutPin, int i2cAddress) : xShutPin(xShutPin), i2cAddress(i2cAddress) {
    pinMode(xShutPin, OUTPUT);

    digitalWrite(xShutPin, LOW);  // erst ausschalten
    delay(10);  // warte bis er aus ist

    digitalWrite(xShutPin, HIGH);
    delay(10);  // warte bis er an ist

    if (!sensor.init()) {
        while (1) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
        }
    }
    sensor.setAddress(i2cAddress);
    sensor.setTimeout(500);
}

// @returns distance in mm
int ToFSensor::getDistance() {
    return sensor.readRangeSingleMillimeters();
}