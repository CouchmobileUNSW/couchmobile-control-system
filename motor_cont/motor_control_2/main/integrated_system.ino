#ifdef INTEGRATED_SYSTEM

// Libraries
#include "src/RobotBase.h"
#include "src/Stanley.h"
#include "src/Euler.h"
#include "src/PathReader.h"

// Robot
RobotBase robot;

// Odometry
Pose pose;
Euler ode;

// PID the input values to achieve a slower response
// The motor control should have close to optimal response
PID pidV, pidW;

// EMERGENCY STOP

void setup() {

  // Serial debug
  #ifdef DEBUG
    debugSerial.println(F("Starting program"));
  #endif

  // Flush buffer
  //while(NeoSerial.available()) NeoSerial.read();

  // Led debug
  pinMode(EMERGENCY_STOP_PIN, INPUT);

  // Setup PID for v and w
  pidV = PID(PID_V_KP, PID_V_KI, PID_V_KD, PID_V_MIN, PID_V_MAX, PID_V_IMAX);
  pidW = PID(PID_W_KP, PID_W_KI, PID_W_KD, PID_W_MIN, PID_W_MAX, PID_W_IMAX);

  // Setup robot
  robot.begin();
  robot.setSpeed(0, 0);
}

// State machine for motor controllers
uint8_t stateTrack, statePoseSend;

void loop() {
  static uint32_t sampleLast = millis();
  // Update pose and control speed
  if(robot.sampleData()) {
    // Control speed
    robot.drive();

    #ifdef DEBUG  // Print data
      logTime();
    #endif
  }

  // Update path tracker
  bool updateControl = true;
  if(updateControl) {
    // Run controller based on inputs
    float v_d = 0.0;
    float w_d = 0.0;
    
    // Set speed inputs
    if(!digitalRead(EMERGENCY_STOP_PIN)) {
      robot.setSpeed(v_d, w_d);
    }
  }

  if(digitalRead(EMERGENCY_STOP_PIN)) {
    robot.setSpeed(0,0);
  }
}

// Prints data
void printData() {
  logTime();
  debugSerial.println();  
}

#endif
