#ifdef MOTOR_LINEAR_SPEED
#define MOTOR_LINEAR_SPEED

#include "src/Motor.h"

// Macros
#define SAMPLE_TIME 8e3
#define PLOTTER

// Create motor object
Motor leftMotor(LEFT_MOTOR, SAMPLE_TIME);

void setup() {
  // Start up serial
  Serial.begin(115200);
  
  // Config motors
  leftMotor.begin();

  // Set PWM to middle of input range
  leftMotor.setSpeed(0);
}

// Variables to take in Serial inputs
float v_d = 0;          // desired speed (m/s)

void loop() {
  // Update every T time
  if(leftMotor.sampleData()) {
    leftMotor.controlSpeed();
    printData();
  }
  
  // Take in Serial input if available
  while(Serial.available() > 0) {
    v_d = Serial.parseFloat();
    leftMotor.setSpeed(v_d);
  }
}

// Prints data
void printData() {
  // Get data
  float t = leftMotor.getCurrTime();        // microseconds
  float v_a = leftMotor.getSpeed();         // m/s
  float v_d = leftMotor.getDesiredSpeed();  // m/s
  float e = leftMotor.getError();           // m/s

  // Print data
  #ifndef PLOTTER
    Serial.print("t: "); Serial.print(t);
    Serial.print("  v_a: "); Serial.print(v_a, 5);
    Serial.print("  v_d: "); Serial.print(v_d, 5);
    Serial.print("  e: "); Serial.print(e, 5);
  #endif
  // Plot data
  #ifdef PLOTTER
    Serial.print(v_d, 5); Serial.print(", ");
    Serial.print(v_a, 5); Serial.print(", ");
    Serial.print("0, 2");
  #endif
  Serial.println();  
}

#endif
