#include "PID.h"

// Config
PID::PID(float _Kp, float _Ki, float _Kd, float _T)
    : Kp(_Kp), Ki(_Ki), Kd(_Kd), T(_T) {
}

// Get error gains
void PID::getErrorGains(float *e_gains, int numel) {
    // Set gains: e_gains[0]*e(k) + e_gains[1]*e(k-1) + ...
    e_gains[0] = Kp + (Ki*T)/2 + Kd/T;
    e_gains[1] = -Kp + (Ki*T)/2 - 2*Kd/T;
    e_gains[2] = Kd/T;  
    
    // Set everything else to zero
    for(int i = 3; i < numel; i++) {
        e_gains[i] = 0;
    }
}

// Get control effort gains
void PID::getControlEffortGains(float *m_gains, int numel) {
    // Set gains: m_gains[0]*m(k-1) + m_gains[1]*m(k-2) + ...
    m_gains[0] = 1;

    // Set everything else to zero
    for(int i = 1; i < numel; i++) {
        m_gains[i] = 0;
    } 
}