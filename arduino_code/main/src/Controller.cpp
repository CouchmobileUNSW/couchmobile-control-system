#include "Controller.h"

// --------Config--------
// Contructor
Controller::Controller() {
    
}   

// Set gains
#ifdef CONTROL_DIRECT
void Controller::setGains(float *e_in, uint8_t _N_e, float *m_in, uint8_t _N_m) {
    // Define number of elements
    N_e = _N_e;
    N_m = _N_m;

    // Copy coefficients
    int i;
    for(i = 0; i < N_e; i++) {
        e_gains[i] = e_in[i];
    }
    for(i = 0; i < N_m; i++) {
        m_gains[i] = m_in[i];
    }
}
#elif defined(CONTROL_PID)
Controller::Controller(float Kp, float Ki, float Kd, float outMin, float outMax, float iMax) {
    pid = PID(Kp, Ki, Kd, outMin, outMax, iMax);
    setRange(outMin, outMax);
}

void Controller::setGains(float Kp, float Ki, float Kd) {
    pid.Kp = Kp;
    pid.Ki = Ki;
    pid.Kd = Kd;
}

void Controller::setIntegralMax(float iMax) {
    pid.iMax = iMax;
}
#endif

// Set controller limits
void Controller::setRange(float min, float max) {
    m_min = min;
    m_max = max;
#ifdef CONTROL_PID
    pid.outMin = min;
    pid.outMax = max;
#endif
}

// --------Controller functions--------
#ifdef CONTROL_DIRECT
float Controller::getControlEffort(float e) {
    float m = 0;
    uint8_t i;

    // Insert current error into e_history
    e_history.insert(e);

    // Add error components multiplied by their gains
    for(i = 0; i < N_e; i++) {
        float tmp = e_history.peek(i);
        m += e_gains[i] * tmp;
    }

    // Add control effort components multipled by their gains
    for(i = 0; i < N_m; i++) {
        float tmp = m_history.peek(i);
        m += m_gains[i] * tmp;
    }

    // Make sure control effort is within the limits
    m = saturateControlEffort(m);

    // Insert current control effort into m_history
    m_history.insert(m);

    return m;
}
#elif defined(CONTROL_PID)
float Controller::getControlEffort(float e) {
    _filter.push(e);
    e = _filter.value();
    return pid.pid(e);
}
#endif

float Controller::getControlEffort(float w_d, float w_a) {
#ifdef CONTROL_PID
    if (abs(w_d) <= 0.001 && w_a == 0.0 && pid.getIntegral() <= 30.0) {
        if (stationaryTicks > 200) {
            pid.setIntegral(0);
        } else {
            stationaryTicks++;
        }
    } else {
        stationaryTicks = 0;
    }
#endif
    return getControlEffort( w_d - w_a );
}

// --------Debug--------
// Prints controller configurations
void Controller::printSettings() {
    uint8_t i;

    // Print e_gains
    //Serial.print("e_gains: ");
    //for(i = 0; i < N_e; i++) {
    //    Serial.print(e_gains[i]);
    //    Serial.print(" ");
    //}
    //Serial.println();

    // Print m_gains
    //Serial.print("m_gains: ");
    //for(i = 0; i < N_m; i++) {
    //    Serial.print(m_gains[i]);
    //    Serial.print(" ");
    //}
    //Serial.println();

    // Print m_limits
    //Serial.print("m_range: ");
    //Serial.print(m_min); Serial.print(" ");
    //Serial.print(m_max);

    //Serial.println();
}

// Prints ring buffers
void Controller::printHistory() {
    // Print e_gains
    //Serial.print("e_history: ");
    //e_history.printBuffer();

    // Print m_gains
    //Serial.print("m_history: ");
    //m_history.printBuffer();
}

// Prints error and control output
void Controller::printData() {
    //Serial.print("e: "); 
    //Serial.print(e_history.peek(0)); Serial.print(" ");
    //Serial.print(m_history.peek(0));
    //Serial.println();
}

// Helper function
float Controller::saturateControlEffort(float m) {
    if(m < m_min) {
        m = m_min;
    }
    else if(m > m_max) {
        m = m_max;
    }
    return m;
}