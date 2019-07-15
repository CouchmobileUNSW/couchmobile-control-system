#ifndef PID_H
#define PID_H

class PID {
private:
    // Controller gains
    float Kp;   // proportional component
    float Ki;   // integral component
    float Kd;   // derivative component
    float T;    // sample time (s)

public:
    // Config
    PID(float _Kp, float _Ki, float _Kd, float _T);

    // Get gains
    void getErrorGains(float *e_gains, int numel);
    void getControlEffortGains(float *m_gains, int numel);
};

#endif