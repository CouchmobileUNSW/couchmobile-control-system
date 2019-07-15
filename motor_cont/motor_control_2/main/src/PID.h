#ifndef PID_H
#define PID_H

#include "Arduino.h"

class PID {
private:
    initPID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax);
public:
    // PID gains
    float Kp, Ki, Kd;

    // Saturate outputs
    float outMin, outMax;
    
    // Saturate integral to prevent integral windup
    float iMax;
    
    PID();
    PID(float Kp, float Ki, float Kd, float outMin, float outMax);
    PID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax);
    float pid(const float& _delta);
};

#endif