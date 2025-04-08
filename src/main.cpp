// region Includes
#include <Arduino.h>
#include <DynamixelShield.h>
#include <Engine.h>
#include <ToFSensor.h>
#include <UltrasonicSensor.h>
#include <Wire.h>

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
int distanceThreshold = 200;  // mm
const int motorSpeed = 100;

Engine *engine = nullptr;
// ToFSensor *frontSensor = nullptr;
// ToFSensor *leftSensor = nullptr;
UltrasonicSensor *frontSensor = nullptr;
UltrasonicSensor *leftSensor = nullptr;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(9600);

  Wire.begin();

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  engine = new Engine();

  frontSensor = new UltrasonicSensor(trigPinFront, echoPinFront);
  leftSensor = new UltrasonicSensor(trigPinLeft, echoPinLeft);
  // frontSensor = new ToFSensor(11, 0x28);
  // leftSensor = new ToFSensor(12, 0x29);

  digitalWrite(ledPin, !running);
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

    if (frontDistance < distanceThreshold) {
      engine->right(motorSpeed);
    } else if (leftDistance < distanceThreshold / 2) {
      engine->forward(motorSpeed);
    } else if (leftDistance < distanceThreshold / 4) {
      engine->right(motorSpeed);
    } {
      engine->left(motorSpeed);
    }
  } else {
    engine->stop();
  }
}