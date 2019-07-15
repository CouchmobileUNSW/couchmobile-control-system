/*
 * Written by Matthew Vong
 * Unit test for PWM output
 * USE: Takes in an input from Serial and outputs PWM signal
 * Must specify the pin in MotorPWM constructor
 * Must specify the timer of the pin in Motor.begin(timer)
 * All time units are in microseconds
 */

#ifdef PWM

#include "src/MotorPWM.h"

// PWM pins and timers
const int pin = PB9;
const int timer = 4;

// PWM configurations
int period = 3000;  // microseconds
int t_min = 1000;   // microseconds
int t_max = 2000;   // microseconds

// User defined range
int in_min = -1024;
int in_max = 1024;

// Construct MotorPWM object
MotorPWM left(pin, timer);

void setup() {
  // Setup Serial
  Serial.begin(115200);
  Serial.println("Starting program");

  // Configure pwm settings
  left.setInputPulse(period, t_min, t_max);
  left.setRange(in_min, in_max);
  left.begin();

  // Print settings
  Serial.println("Config finished");
  left.printSettings();

  // Set PWM to middle of input range
  left.writeValue(0);
}

// Variables to take in Serial inputs
float input = 0;
bool flag = false;
int pwm_output;

void loop() {
  // Take in Serial input if available
  while(Serial.available() > 0) {
    input = Serial.parseFloat();
    flag = true;
  }

  // Change pwm_output according to input
  if(flag) {
    left.writeValue(input);
    pwm_output = left.getPWMOutput();
    
    Serial.print("Input: "); 
    Serial.print(input); Serial.print(" ");
    Serial.println(pwm_output);
    flag = false;
  }
}

#endif



