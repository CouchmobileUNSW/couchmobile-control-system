#include "Motor.h"

// Config
Motor::Motor(int x, unsigned int T) 
    : MotorBase(x, T) {
}

// Initialise and set up gains
void Motor::begin() {
    MotorBase::begin();
    setGains(e_gains, N_e, m_gains, N_m);
}

// Setters
void Motor::setSpeed(float v) {
    float w_d = saturate(v/WHEEL_RADIUS, -MAX_RADIAN_SPEED, MAX_RADIAN_SPEED);
    setRadianSpeed(w_d);
}

// Getters
float Motor::getDesiredSpeed() {
    return getDesiredRadianSpeed()*WHEEL_RADIUS;
}

float Motor::getSpeed() {
    return getRadianSpeed()*WHEEL_RADIUS;
}

float Motor::getError() {
    return (getDesiredSpeed() - getSpeed());
}

// Helper functions
float Motor::saturate(float x, float min, float max) {
    if(x < min) {
        x = min;
    }
    else if(x > max) {
        x = max;
    }
    return x;
}