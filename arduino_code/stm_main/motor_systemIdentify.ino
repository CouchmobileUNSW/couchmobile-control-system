/*
 * This is a integration test with PWM and encoders
 * Specify the the QUAD_TIMER_x, pwm pin, pwm timer number and SAMPLE_TIME
 */

#ifdef MOTOR_IDENTIFY

// Macros
//#define DEBUG
#define PLOTTER
#define SAMPLE_TIME 8e3   // microseconds

#include "src/MotorBase.h"

MotorBase leftMotor(LEFT_MOTOR, SAMPLE_TIME);

// Variables to take in Serial inputs
float input = 1024;
bool flag = false;

void setup() {
  // Start up serial
  Serial.begin(115200);

  // Config motors
  leftMotor.begin();
  leftMotor.printSettings();   // print motor settings

  // Set PWM to middle of input range
  leftMotor.writeValue(input);
}

void loop() {
  // Update every SAMPLE_TIME
  if(leftMotor.sampleData()) {
    printData();
  }

  // Take in Serial input if available
  while(Serial.available() > 0) {
    input = Serial.parseFloat();
    flag = true;
  }

  // Change pwm_output according to input
  if(flag) {
    leftMotor.writeValue(input);
    flag = false;
  }
}

// Print data
void printData() {
  // Get speed data
  float w = leftMotor.getTickSpeed();
  float t = leftMotor.getCurrTime();
  
  #ifdef DEBUG
    Serial.print(leftMotor.getPWMOutput()); Serial.print(", ");  
    Serial.print(leftMotor.getPrevTicks()); Serial.print(", ");
    Serial.print(leftMotor.getCurrTicks()); Serial.print(", ");
    Serial.print(leftMotor.getDeltaTicks()); Serial.print(", ");
  #endif
  
  // Print details
  #ifdef PLOTTER
    Serial.print("0, ");
    Serial.print("40, ");
  #endif
  #ifndef PLOTTER
    Serial.print(t); Serial.print(", ");
  #endif
  
  Serial.print(w); Serial.println();
}

#endif
