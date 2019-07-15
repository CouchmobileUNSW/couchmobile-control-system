#ifdef ROBOT_DRIVER_YAW

#include "src/Robot.h"
#include <libmaple/iwdg.h>

// Watchdog timer
#define WATCHDOG_TIME 800 // ms
#define iwdg_init_ms(N) iwdg_init(IWDG_PRE_256,((N)/5)) // NOTE: watchdog is not that accurate: 6.4ms

// Create robot
Robot robot;

void setup() {
  // Setup Serial
  Serial.begin(115200);
  Serial.println("Starting program");

  // Initialise watchdog
  //iwdg_init_ms(WATCHDOG_TIME);

  // Setup robot
  robot.begin();
  robot.setSpeedYaw(0, 0);
}

void loop() {
  // Update every SAMPLE_TIME
  if(robot.sampleData()) {
    robot.drive();
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
  bool flag = false;
  
  // Take in Serial input if available
  while(Serial.available() > 0) {
    v = Serial.parseFloat();
    w = Serial.parseFloat();
    flag = true;
  }

  // Change pwm_output according to input
  if(flag) {
    robot.setSpeedYaw(v, w);
    flag = false;
  }  
}

// Prints data
void printData() {
  // Get data
  float v_d = robot.getVd();
  float v_cm = robot.getVcm();
  float yaw_d = robot.getDesiredYaw();
  float yaw_a = robot.getYaw();
  float e_yaw = robot.getYawError();

  // Print data
//  Serial.print(v_d); Serial.print(", ");
//  Serial.print(v_cm); Serial.print(", ");
  Serial.print(yaw_d); Serial.print(", ");
  Serial.print(yaw_a); Serial.print(", ");
  Serial.print(e_yaw); Serial.print(", ");
  Serial.print(robot.getWd());
  Serial.println();  
}

#endif
