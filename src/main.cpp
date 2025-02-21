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

const int echoPin = 3;
const int trigPin = 4;
const int ledPin = 9;
const int switchPin = 10;
const int pin5V = 12;
int switchState = 1;

Engine engine;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  // set pin 5V to HIGH
  pinMode(pin5V, OUTPUT);
  digitalWrite(pin5V, HIGH);

  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
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
      engine.forward(20);
    } else {
      engine.stop();
    }
  }

  if (getDistanceFront() < 15) {
    engine.stop();
    switchState = switchState == 1 ? 0 : 1;

    digitalWrite(ledPin, switchState);
  }
}

int getDistanceFront() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  return (pulseIn(echoPin, HIGH) * 0.034) / 2;
}