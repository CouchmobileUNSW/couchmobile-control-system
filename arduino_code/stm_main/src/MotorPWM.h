#ifndef MOTORPWM_H
#define MOTORPWM_H

#include "Arduino.h"
#include "HardwareTimer.h"

/* NOTE: 
    - PWM maps from 0-maxduty, where maxduty <= 65535
    - DO NOT BLINDLY USE 65335. This changes with PWM freq.
    - Ensure PWM pins with the same TIMER have the same freq
*/

class MotorPWM {
private:
    // Hardware settings
    uint8_t pin;            // PWM pin
    uint8_t timer_num;      // PWM timer number
    uint32_t period;        // PWM input period (microseconds)

    // Define range limits
    int t_min, t_max;       // PWM input pulse range (microseconds)
    int in_min, in_max;     // user defined range
    int out_min, out_max;   // 0-65535 PWM units

    // PWM data
    int max_duty;           // automatically set up by hardware timer
    int pwm_out;            // pwm output for debug

public:
    // Config hardware
    MotorPWM(uint8_t _pin, uint8_t _timer_num);

    // PWM settings
    void setInputPulse(uint32_t _period, int _t_min, int _t_max);
    void setRange(int _in_min, int _in_max);
    void begin();

    // PWM control
    void writeValue(float value);    // Write PWM using custom range
    int getPWMOutput();

    // Helper function
    int mapFloatPWM(float value);

    // Print config
    void printSettings();
};

#endif