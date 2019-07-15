#ifndef ROBOT_H
#define ROBOT_H

#include "RobotBase.h"
#include "Controller.h"

// yaw controller parameters
static float Kw = 4;         // tau = 1/K
static float w_max = 3;   // rad/s

// Same as robot base but with a yaw controller
class Robot: public RobotBase {
private:
    // Controller for yaw->w
    Controller yawCont;

    // Variables
    float yaw_d;    // desired yaw (rad)
    float e;        // error in yaw (rad)
    float v;        // speed (m/s)
public:
  // Config
  void begin();

  // Drive - set speed and yaw
  void setSpeedYaw(float _v, float yaw);
  bool sampleData();

  // Getters
  float getDesiredYaw();          // rad
  float getYawError();            // rad

  // Helper function
  float normalizeAngle(float x);  // rad
};


#endif
