#include <iostream>
#include "PID.h"

using namespace std;

void printArray(float *A, int n) {
    for(int i = 0; i < n; i++) {
        printf("%.5f ", A[i]);
    }
    printf("\n");
}

int main(void) {
    float Kp = 52.5, Ki = 732, Kd = 0.313, Tf = 0.0257, Ts = 0.008;
    PID pid(Kp, Ki, Kd, Ts);

    float e_gains[5];
    float m_gains[5];

    // Load gains
    pid.getErrorGains(e_gains, 5);
    pid.getControlEffortGains(m_gains, 5);


    // Print arrays
    printArray(e_gains, 5);
    printArray(m_gains, 5);

    return 0;
}