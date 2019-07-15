#ifndef ROBOT_BASE_H
#define ROBOT_BASE_H

#include "Motor.h"
#include "myBNO080.h"

// Car parameters
#define WHEEL_DIST 0.185  // distance between wheel centres (m)

// Sample times
#define SAMPLE_TIME 8e3   // microseconds
#define RESET_TIME 50e3   // microseconds

class RobotBase {
private:
    // Motors
    Motor leftMotor;
    Motor rightMotor;
    myBNO080 imu;

    // Speed actual/desired
    float v_cm, v_d;    // velocity of centre of wheels
    float w_cm, w_d;    // angular velocity of centre

public:
    // Config
    RobotBase(unsigned int T = SAMPLE_TIME, unsigned int resetTime = RESET_TIME);
    void begin();

    // Drive - call in this order
    void setSpeed(float v, float w);
    bool sampleData();
    void drive();

    // Getters
    float getVcm();         // m/s
    float getWcm();         // rad/s
    float getYaw();         // rad
    float getVd();          // m/s
    float getWd();          // rad/s
    float getDeltaTime();   // s

    // Debug
    float getLeftSpeed();           // m/s
    float getRightSpeed();          // m/s
    float getDesiredLeftSpeed();    // m/s
    float getDesiredRightSpeed();   // m/s
    float getYawDeg();              // deg
};


#endif
