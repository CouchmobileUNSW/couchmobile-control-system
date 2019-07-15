#ifndef MOTOR_H
#define MOTOR_H

#include "MotorBase.h"

// Wheel parameters
#define WHEEL_RADIUS 0.05       // m
#define MAX_RADIAN_SPEED 36.65  // rad/s

// Motor control parameters
static int N_e = 3, N_m = 2; 
static float e_gains[] = {64.6221109336773, -107.0597795006965, 44.2599059086172};
static float m_gains[] = {1.688682860224775, -0.688682860224775};

// Identical to MotorBase. Specify m/s instead of rad/s
class Motor: public MotorBase {
public:
    // Config
    Motor(int x, unsigned int T);   // which motor? LEFT_MOTOR or RIGHT_MOTOR
    void begin();

    // Setters
    void setSpeed(float v);

    // Getters
    float getDesiredSpeed();
    float getSpeed();
    float getError();

    // Helper functions
    float saturate(float x, float min, float max);
};

#endif