#include "PID.h"

PID::PID() {
    
}

PID::PID(float Kp, float Ki, float Kd, float outMin, float outMax)
    : Kp(Kp), Ki(Ki), Kd(Kd), outMin(outMin), outMax(outMax) {
}

PID::PID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax)
    : Kp(Kp), Ki(Ki), Kd(Kd), outMin(outMin), outMax(outMax), iMax(iMax) {
        
}

PID::initPID(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax) {
    
}

float PID::pid(const float& _delta) {
    static float lastDelta = 0;
    static float integral = 0;
    static uint32_t prevTime = micros();
    
    uint32_t currTime = micros();
    float dt = (float) (uint32_t(currTime - prevTime))/1000000.0;
    
    integral += _delta * dt;
    
    if (iMax == 0) {
        // Do nothing
    } else if (integral < -iMax) {
        integral = -iMax;
    } else if (integral > iMax) {
        integral = iMax;
    }
    
    float diff = (_delta - lastDelta)/dt;
    
    float p = Kp * _delta;
    float i = Ki * integral;
    float d = Kd * diff;
    
    lastDelta = _delta;
    prevTime = currTime;
    
    NeoSerial.print("Delta: ");
    NeoSerial.println(_delta);
    
    NeoSerial.print(p);
    NeoSerial.print(",");
    NeoSerial.print(i);
    NeoSerial.print(",");
    NeoSerial.print(d);
    NeoSerial.println("");
    
    
    float output = p + i + d;

    // Saturate output
    if(output < outMin) output = outMin;
    else if(output > outMax) output = outMax;

    return output;
}