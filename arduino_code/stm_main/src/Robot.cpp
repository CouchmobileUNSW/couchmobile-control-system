#include "Robot.h"

// Configure yaw controller
void Robot::begin() {
    yawCont.setGains((&Kw), 1, NULL, 0);
    yawCont.setRange(-w_max, w_max);
    RobotBase::begin();
}

// Set desired speed and direction
void Robot::setSpeedYaw(float _v, float yaw) {
    // Update variables
    v = _v;
    yaw_d = yaw;

    // Find yaw error
    e = normalizeAngle(yaw_d - getYaw());

    // Find control effort
    float m = yawCont.getControlEffort(e);

    // Set parameters
    RobotBase::setSpeed(v, m);
}

// Update data for robot
// Return true if data was updated
bool Robot::sampleData() {
    // Update data if available
    if(RobotBase::sampleData()) {
        e = normalizeAngle(yaw_d - getYaw());
        float m = yawCont.getControlEffort(e);
        RobotBase::setSpeed(v, m);
        return true;
    }
    return false;
}

// Getters
float Robot::getDesiredYaw() {
    return yaw_d;
}

float Robot::getYawError() {
    return e;
}

// Helper function
// Accounts for angle wrapping [-pi, pi]
float Robot::normalizeAngle(float x) {
    // Check for wrapping
    if(x > PI) {
        x -= 2*PI;
    }
    else if(x < -PI) {
        x += 2 * PI;
    }
    return x;
}
