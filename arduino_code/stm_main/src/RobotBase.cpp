#include "RobotBase.h"

// Config
RobotBase::RobotBase(unsigned int T, unsigned int resetTime)
    : leftMotor(LEFT_MOTOR, T), rightMotor(RIGHT_MOTOR, T),
        imu(T/1e3, resetTime/1e3) {
}

// Initialise robot
void RobotBase::begin() {
    leftMotor.begin();
    rightMotor.begin();
    imu.begin();
}

// Sets desired v and w
void RobotBase::setSpeed(float v, float w) {
    // Save desired speeds
    v_d = v;
    w_d = w;

    // Calculate individual wheel speeds
    float w_L = (2*v - w*WHEEL_DIST) / 2;
    float w_R = (2*v + w*WHEEL_DIST) / 2;

    // Set motor speeds
    leftMotor.setSpeed(w_L);
    rightMotor.setSpeed(w_R);
}

// Update data for robot
// Returns true if data was updated
bool RobotBase::sampleData() {
    // Update data for both motors
    if(leftMotor.sampleData() && rightMotor.sampleData() && imu.update()) {
        // Update robot data
        v_cm = (rightMotor.getSpeed() + leftMotor.getSpeed())/2;
        w_cm = (rightMotor.getSpeed() - leftMotor.getSpeed())/WHEEL_DIST;
        return true;
    }
    return false;
}

// Drive robot
void RobotBase::drive() {
    // Control speed
    leftMotor.controlSpeed();
    rightMotor.controlSpeed();
}

// Get velocity
float RobotBase::getVcm() {
    return v_cm;
}

// Get anguar velocity
float RobotBase::getWcm() {
    return w_cm;
}

// Gets yaw (since IMU IS UPSIDE DOWN)
float RobotBase::getYaw() {
    return -imu.getYaw();
}

// Get desired velocity
float RobotBase::getVd() {
    return v_d;
}

// Get desired anguar velocity
float RobotBase::getWd() {
    return w_d;
}

// Get sample time
float RobotBase::getDeltaTime() {
    return leftMotor.getDeltaTime(); // use either one
}

// Debug
float RobotBase::getLeftSpeed() {
    return leftMotor.getSpeed();
}

float RobotBase::getRightSpeed() {
    return rightMotor.getSpeed();
}

float RobotBase::getDesiredLeftSpeed() {
    return leftMotor.getDesiredSpeed();
}

float RobotBase::getDesiredRightSpeed() {
    return rightMotor.getDesiredSpeed();
}

// Gets yaw
float RobotBase::getYawDeg() {
    return imu.getYawDeg();
}
