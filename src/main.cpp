// region Includes
#include <UltrasonicSensor.h>
#include <DynamixelShield.h>
#include <Engine.h>

#include "Arduino.h"

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(7, 8);  // DYNAMIXELShield UART RX/TX
#define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
#define DEBUG_SERIAL SerialUSB
#else
#define DEBUG_SERIAL Serial
#endif
// endregion Includes

// region Pins
const int echoPinFront = 3;
const int trigPinFront = 4;
const int echoPinLeft = 5;
const int trigPinLeft = 6;
const int switchPin = 7;
const int ledPin = 9;
// endregion Pins

volatile bool running = false;
int distanceThreshold = 15;  // cm
const int motorSpeed = 20;

Engine *engine = nullptr;
UltrasonicSensor *frontSensor = nullptr;
UltrasonicSensor *leftSensor = nullptr;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(9600);

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  engine = new Engine();

  frontSensor = new UltrasonicSensor(trigPinFront, echoPinFront);
  leftSensor = new UltrasonicSensor(trigPinLeft, echoPinLeft);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    while (digitalRead(switchPin) == LOW) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    running = !running;
    digitalWrite(ledPin, !running);  // HIGH on standby
  }
  if (running) {
    int frontDistance = frontSensor->getDistance();
    int leftDistance = leftSensor->getDistance();

    if (frontDistance < distanceThreshold && leftDistance < distanceThreshold) {
      engine->right(motorSpeed);
    } else if (leftDistance > distanceThreshold) {
      engine->left(motorSpeed);
    } else {
      engine->forward(motorSpeed);
    }
  } else {
    engine->stop();
  }
}