
#ifdef MOTOR_IDENTIFY_2
#include "src/MotorPWM.h"
#include "src/Config.h"
#include "src/MotorBase.h"
/* CALIBRATION SEQUENCE */
/*
    1. Power ON the speed controller.
    2. Press and hold the Cal button. After a moment, the
    LED indicator on the Victor will begin alternating
    between RED and GREEN to indicate a cal mode.
    3. While continuing to hold the Cal button, move the
    joystick to the maximum and minimum positions.
    This can be done in any order and as many times as
    desired.
    4. While continuing to hold the Cal button, return the
    joystick to center (neutral position).
    5. Release the Cal button.
    6. A flashing GREEN indicator confirms a successful
    calibration.
    7. A flashing RED indicator denotes an unsuccessful
    calibration.
    An unsuccessful calibration occurs when either:
    a) Insufficient joystick travel was detected in forward
    and/or reverse.
    b) The trim tab is too far from center.
    c) The Joystick 
 */

// Pin 6 = default left motor; pin 7 = default right motor
MotorBase leftMotor(LEFT_MOTOR, 8e3);
 float pwmVal = 0;

void setup() {
  // Start up serial
  NeoSerial.begin(115200);
  leftMotor.begin();
  leftMotor.printSettings();   // print motor settings
  leftMotor.writeValue(0);


  digitalWrite(A15, LOW);
  delay(3000);
  digitalWrite(A15,HIGH);
  float maxVal = 500;
  float minVal = -500;
  const int delayTime = 10;
  const int numIncrements = 100;
  for (int rep = 0; rep < 1; rep++) {
    for (int i = 0; i <= numIncrements; i++) {
      pwmVal = (float) minVal + (maxVal - minVal)/(numIncrements) * i;
      leftMotor.writeValue(pwmVal);
      for (int j = 0; j < 20; j++) {
        if(leftMotor.sampleData()) {
          printData();
        }
        delay(delayTime);
      }
    }
    delay(200);
    for (int i = 0; i <= numIncrements; i++) {
      if(leftMotor.sampleData()) {
        printData();
      }
      pwmVal = (float) maxVal + (minVal - maxVal)/(numIncrements) * i;
      leftMotor.writeValue(pwmVal);
      for (int j = 0; j < 10; j++) {
        if(leftMotor.sampleData()) {
          printData();
        }
        delay(delayTime);
      }
    }
    delay(200);
  }
  leftMotor.writeValue(0);
}

void loop() {
  digitalWrite(A15, HIGH);
  delay(100);
  digitalWrite(A15, LOW);
  delay(100);
}


// Print data
void printData() {
  // Get speed data
  float w = leftMotor.getTickSpeed();
  float t = leftMotor.getCurrTime();
  
  NeoSerial.print(w); NeoSerial.print(", ");
  NeoSerial.print(pwmVal);
  NeoSerial.println();
}
#endif
