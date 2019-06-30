#include "Arduino.h" 
#include <Servo.h>

// Motor variables
#define motorPin 3
#define motorPin2 5
volatile long val;
Servo motor;  // create servo object for the PWM
Servo motor2;
 
void setup()
{
  Serial.begin(9600);

  motor.attach(motorPin);  // attach the motor to pin 9 for PWM
  motor2.attach(motorPin2);
}
 
void loop()
{
  val = 100;
  motor.write(val);
  motor2.write(val);
  delay(20);
}
