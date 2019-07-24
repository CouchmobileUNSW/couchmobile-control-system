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
 MotorPWM pwm(7);
 float pwmVal = 0;

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

  pwm.setInputPulse(PWM_PERIOD, PWM_PULSE_LOW, PWM_PULSE_HIGH);
  pwm.setRange(CONTROL_MIN, CONTROL_MAX);
  pwm.begin();
  digitalWrite(A15, LOW);
  pwm.writeValue(0);
  delay(5000);
  digitalWrite(A15,HIGH);
  const int numIncrements = 1000;
  for (int rep = 0; rep < 2; rep++) {
    for (int i = 0; i <= numIncrements; i++) {
      pwmVal = (float) CONTROL_MIN + (CONTROL_MAX - CONTROL_MIN)/numIncrements * i;
      pwm.writeValue(pwmVal);
      NeoSerial.print("PWMVAL: ");
      NeoSerial.println(pwmVal);
      delay(5);
    }
    delay(200);
    for (int i = 0; i <= numIncrements; i++) {
      pwmVal = (float) CONTROL_MAX + (CONTROL_MIN - CONTROL_MAX)/numIncrements * i;
      pwm.writeValue(pwmVal);
      NeoSerial.print("PWMVAL: ");
      NeoSerial.println(pwmVal);
      delay(5);
    }
    delay(200);
  }
  pwm.writeValue(0);
}

void loop() {
  digitalWrite(A15, HIGH);
  delay(100);
  digitalWrite(A15, LOW);
  delay(100);
}
#endif
