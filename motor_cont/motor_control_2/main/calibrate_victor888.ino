#ifdef CALIBRATE
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
 MotorPWM pwm(6);
 float pwmVal = 0;

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

  pwm.setInputPulse(PWM_PERIOD, PWM_PULSE_LOW, PWM_PULSE_HIGH);
  pwm.setRange(CONTROL_MIN, CONTROL_MAX);
  pwm.begin();

  pwm.writeValue(0);
  delay(3000);
  const int numIncrements = 1000;
  for (int i = 0; i < numIncrements; i++) {
    pwmVal = (float) CONTROL_MIN + (CONTROL_MAX - CONTROL_MIN)/numIncrements;
    pwm.writeValue(pwmVal);
    NeoSerial.print("PWMVAL: ");
    NeoSerial.println(pwmVal);
    delay(5);
  }
}

void loop() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
#endif
