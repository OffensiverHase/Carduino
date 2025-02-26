#include <Arduino.h>
#include <UltrasonicSensor.h>

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// @returns distance in mm
int UltrasonicSensor::getDistance() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  return ((pulseIn(echoPin, HIGH) * 0.034) / 2) * 10;
}