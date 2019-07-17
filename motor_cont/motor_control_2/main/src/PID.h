#ifndef PID_H
#define PID_H

#include "Arduino.h"
#include "Config.h"

class PID {
private:
    void initPID();
    void initPID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax);
    float lastDelta;
    float integral;
    uint32_t prevTime;
public:
    // PID gains
    float Kp = 0;
    float Ki = 0;
    float Kd = 0;

    // Saturate outputs
    float outMin = -1024;
    float outMax = 1024;
    
    // Saturate integral to prevent integral windup
    float iMax = 0;
    
    PID();
    PID(float Kp, float Ki, float Kd, float outMin, float outMax);
    PID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax);
    
    // Error given by desired - actual value
    float pid(const float& _delta);
};

#endif