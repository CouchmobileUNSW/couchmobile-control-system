/*
 * This is a integration test with PWM and encoders
 * Specify the the QUAD_TIMER_x, pwm pin, pwm timer number and SAMPLE_TIME
 */

#ifdef MOTOR_IDENTIFY

// Macros
//#define DEBUG
//#define PLOTTER
#define SAMPLE_TIME 8e3   // microseconds

#include "src/MotorBase.h"

MotorBase leftMotor(LEFT_MOTOR, SAMPLE_TIME);

// Variables to take in Serial inputs
float input = 0;
bool flag = false;

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

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
  while(NeoSerial.available() > 0) {
    input = NeoSerial.parseFloat();
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
    NeoSerial.print(leftMotor.getPWMOutput()); NeoSerial.print(", ");  
    NeoSerial.print(leftMotor.getPrevTicks()); NeoSerial.print(", ");
    NeoSerial.print(leftMotor.getCurrTicks()); NeoSerial.print(", ");
    NeoSerial.print(leftMotor.getDeltaTicks()); NeoSerial.print(", ");
  #endif
  
  // Print details
  #ifdef PLOTTER
    NeoSerial.print("0, ");
    NeoSerial.print("40, ");
  #endif
  #ifndef PLOTTER
    NeoSerial.print(t); NeoSerial.print(", ");
  #endif
  
  NeoSerial.print(w); NeoSerial.print(", ");
  NeoSerial.print(input);
  NeoSerial.println();
}

#endif
