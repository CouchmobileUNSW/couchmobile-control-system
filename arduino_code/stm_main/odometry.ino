#ifdef ODOMETRY

// Libraries
#include <libmaple/iwdg.h>
#include "src/Robot.h"
#include "src/Euler.h"
#include "src/RK4.h"

// Watchdog timer
#define WATCHDOG_TIME 1000 // ms
#define iwdg_init_ms(N) iwdg_init(IWDG_PRE_256,((N)/5)) // NOTE: watchdog is not that accurate: 6.4ms

// Create robot
Robot robot;

// Odometry
Pose pose;
RK4 ode;

void setup() {
  // Setup serial
  Serial.begin(115200);
  Serial.println("Starting program");

  // Setup robot
  robot.begin();
  robot.setSpeed(0, 0);

  // Initialise watchdog
  //iwdg_init_ms(WATCHDOG_TIME);
}

void loop() {
  // Update every SAMPLE_TIME
  if(robot.sampleData()) {
    robot.drive();
    
    // Update position
    float v_cm = robot.getVcm();
    float yaw = robot.getYaw();
    float dt = robot.getDeltaTime();
    pose = ode.integrate(v_cm, yaw, dt);

    // Print data
    printData();
  }

  // Load data from serial
  readSerial();
  
  // Reset watchdog
  //iwdg_feed();
}

// Load data
void readSerial() { 
  // Variables
  float v, w;
  float flag = false;
  
  // Take in Serial input if available
  while(Serial.available() > 0) {
    v = Serial.parseFloat();
    w = Serial.parseFloat();
    flag = true;
  }

  // Change pwm_output according to input
  if(flag) {
    robot.setSpeed(v, w);
    flag = false;
  }  
}

// Prints data
void printData() {
  // Get data
  float v_d = robot.getVd();
  float v_cm = robot.getVcm();
  float w_d = robot.getWd();
  float w_cm = robot.getWcm();
  float yaw = robot.getYawDeg();

  // Print data
//  Serial.print(v_d); Serial.print(", ");
//  Serial.print(v_cm); Serial.print(", ");
//  Serial.print(w_d); Serial.print(", ");
//  Serial.print(w_cm); Serial.print(", ");
//  Serial.print(yaw);

  // Print position (cm)
  Serial.print(pose.x*1000); Serial.print(", ");
  Serial.print(pose.y*1000); Serial.print(", ");
  Serial.print(pose.yaw * 180/PI);  
  Serial.println();  
}

#endif
