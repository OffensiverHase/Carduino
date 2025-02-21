#include <Arduino.h>
#include <DistanceSensor.h>

DistanceSensor::DistanceSensor(int trigPin, int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int DistanceSensor::getDistance() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  return (pulseIn(echoPin, HIGH) * 0.034) / 2;
}