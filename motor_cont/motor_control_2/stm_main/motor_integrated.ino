#ifdef MOTOR_INTEGRATED
#include "src/MotorBase.h"
#include "src/StandardPID.h"

// Macros
#define SAMPLE_TIME 8e3   // microseconds
#define PLOTTER
#define MANUAL_CONTROL
//#define PID_CONTROL

/// Controller definitions
#ifdef MANUAL_CONTROL
  // Discrete pid
  int N_e = 3; int N_m = 2;
  float e_gains[] = {64.6221109336773, -107.0597795006965, 44.2599059086172};
  float m_gains[] = {1.688682860224775, -0.688682860224775};

  // Ragazinni
//  int N_e = 2; int N_m = 2;
//  float e_gains[] = {25.414338567037372, -23.152173299667442};
//  float m_gains[] = {0.960246186285806, 0.039753813714194};
#endif

#ifdef PID_CONTROL
  int N_e = 3; int N_m = 3;
  float e_gains[3];
  float m_gains[3];

  // Get controller gains
  StandardPID pid(20, 0.8, 0, (float)SAMPLE_TIME/1000);
#endif


// Motor definition
MotorBase leftMotor(LEFT_MOTOR, SAMPLE_TIME);

void setup() {
  // Start up serial
  Serial.begin(115200);

  // PID
  #ifdef PID_CONTROL
    pid.getErrorGains(e_gains, N_e);
    pid.getControlEffortGains(m_gains, N_m);
  #endif

  // Config motors
  leftMotor.begin();
  leftMotor.setGains(e_gains, N_e, m_gains, N_m);
  leftMotor.printSettings();   // print motor settings
}

// Variables to take in Serial inputs
float w_d = 0;          // desired speed (rad/s)

void loop() {
  // Update every T time
  if(leftMotor.sampleData()) {
    leftMotor.controlSpeed();
    printData();
  }
  
  // Take in Serial input if available
  while(Serial.available() > 0) {
    w_d = Serial.parseFloat();
    leftMotor.setRadianSpeed(w_d);
  }
}

// Prints data
void printData() {
  // Get data
  float t = leftMotor.getCurrTime();              // microseconds
  float w_a = leftMotor.getRadianSpeed();         // rad/s
  float w_d = leftMotor.getDesiredRadianSpeed();  // rad/s
  float e = leftMotor.getRadianError();           // rad/s
  float m = leftMotor.getControlEffort();         // user defined range (-1024, 1024);

  // Print data
  #ifndef PLOTTER
    Serial.print("t: "); Serial.print(t);
    Serial.print("  w_a: "); Serial.print(w_a);
    Serial.print("  w_d: "); Serial.print(w_d);
    Serial.print("  e: "); Serial.print(e);
    Serial.print("  m: "); Serial.print(m);
  #endif

  #ifdef PLOTTER
    Serial.print(w_a); Serial.print(", ");
    Serial.print(w_d); Serial.print(", ");
    Serial.print("0, 40");
  #endif

  Serial.println();  
}

#endif
