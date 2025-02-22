// region Includes
#include <DistanceSensor.h>
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
const int echoPin = 3;
const int trigPin = 4;
const int ledPin = 9;
const int switchPin = 10;
const int pin5V = 12;
// endregion Pins

int switchState = 1;

Engine *engine = nullptr;
DistanceSensor *frontSensor = nullptr;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // set pin 5V to HIGH
  pinMode(pin5V, OUTPUT);
  digitalWrite(pin5V, HIGH);

  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(9600);

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  engine = new Engine();

  frontSensor = new DistanceSensor(trigPin, echoPin);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    while (digitalRead(switchPin) == LOW) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    switchState = switchState == 1 ? 0 : 1;
    digitalWrite(ledPin, switchState);

    if (switchState == 1) {
      engine->forward(20);
    } else {
      engine->stop();
    }
  }

  if (frontSensor->getDistance() < 15) {
    engine->stop();
    switchState = 0;

    digitalWrite(ledPin, switchState);
  }
}