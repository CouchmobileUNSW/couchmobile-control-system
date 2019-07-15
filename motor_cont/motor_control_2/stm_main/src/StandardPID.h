#ifndef STANDARD_PID_H
#define PID_H

class StandardPID {
private:
    // Controller gains
    float Kp;   // proportional component
    float Ti;   // integral component
    float Td;   // derivative component
    float T;    // sample time (s)

public:
    // Config
    StandardPID(float _Kp, float _Ti, float _Td, float _T);

    // Get gains
    void getErrorGains(float *e_gains, int numel);
    void getControlEffortGains(float *m_gains, int numel);
};

#endif