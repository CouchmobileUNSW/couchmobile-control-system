#include "StandardPID.h"

// Config
StandardPID::StandardPID(float _Kp, float _Ti, float _Td, float _T)
    : Kp(_Kp), Ti(_Ti), Td(_Td), T(_T) {
}

// Get error gains
void StandardPID::getErrorGains(float *e_gains, int numel) {
    // Set gains: e_gains[0]*e(k) + e_gains[1]*e(k-1) + ...
    // Tustin's rule
    e_gains[0] = Kp * ( Td/T );  
    e_gains[1] = Kp * ( T/(2*Ti) - 2*Td/T - 1 ); 
    e_gains[2] = Kp * ( T/(2*Ti) + Td/T + 1 ); 
    
    // Set everything else to zero
    for(int i = 3; i < numel; i++) {
        e_gains[i] = 0;
    }
}

// Get control effort gains
void StandardPID::getControlEffortGains(float *m_gains, int numel) {
    // Set gains: m_gains[0]*m(k-1) + m_gains[1]*m(k-2) + ...
    m_gains[0] = 1;

    // Set everything else to zero
    for(int i = 1; i < numel; i++) {
        m_gains[i] = 0;
    } 
}