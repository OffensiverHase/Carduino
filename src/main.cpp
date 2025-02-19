#include <DynamixelShield.h>

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

const uint8_t DXL_ID_L = 1;
const uint8_t DXL_ID_R = 2;
const float DXL_PROTOCOL_VERSION = 1.0;

const int ledPin = 9;
const int switchPin = 10;
int switchState = 1;

DynamixelShield dxl;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:

  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(9600);

  // Set Port baudrate to 1000000 bps. This has to match with DYNAMIXEL
  // baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol
  // version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID_R);
  dxl.ping(DXL_ID_L);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID_R);
  dxl.setOperatingMode(DXL_ID_R, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_R);

  dxl.torqueOff(DXL_ID_L);
  dxl.setOperatingMode(DXL_ID_L, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_L);

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
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
    digitalWrite(ledPin, !switchState);

    if (switchState == 0) {
      motor_forward(20);
    } else {
      motor_stop();
    }
  }
}

void motor_forward(int percent) {
  dxl.setGoalVelocity(DXL_ID_R, percent, UNIT_PERCENT);
  dxl.setGoalVelocity(DXL_ID_L, percent - 100, UNIT_PERCENT);
  DEBUG_SERIAL.print("Present Velocity(raw) : ");
  DEBUG_SERIAL.println(dxl.getPresentVelocity(DXL_ID_L));
}

void motor_stop() {
  dxl.setGoalVelocity(DXL_ID_R, 0);
  dxl.setGoalVelocity(DXL_ID_L, 0);
  DEBUG_SERIAL.print("Present Velocity(raw) : ");
  DEBUG_SERIAL.println(dxl.getPresentVelocity(DXL_ID_L));
}