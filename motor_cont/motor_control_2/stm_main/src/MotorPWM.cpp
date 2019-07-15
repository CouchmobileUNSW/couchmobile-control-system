
#include "MotorPWM.h"

// Constructor
MotorPWM::MotorPWM(uint8_t _pin, uint8_t _timer_num)
    : pin(_pin), timer_num(_timer_num) {
}

// Set high time limits
void MotorPWM::setInputPulse(uint32_t _period, int _t_min, int _t_max) {
    period = _period;
    t_min = _t_min;
    t_max = _t_max;
}

// Set PWM range
void MotorPWM::setRange(int _in_min, int _in_max) {
    in_min = _in_min;
    in_max = _in_max;
}

// Sets the frequency of the timers
// Initialises PWM based on ranges
void MotorPWM::begin() {
    // Set pin mode to PWM
    pinMode(pin, PWM);

    // Create timer object
    HardwareTimer pwmTimer(timer_num);

    // Set pwm period and refresh
    pwmTimer.pause();
    max_duty = pwmTimer.setPeriod(period);
    pwmTimer.refresh();
    pwmTimer.resume();

    // Define out_min and out_max
    out_min = (t_min * max_duty)/period;
    out_max = (t_max * max_duty)/period;
}

// Write to PWM using the value in custom range
void MotorPWM::writeValue(float value) {
    // Map value to pwm range
    pwm_out = mapFloatPWM(value);

    // Saturate limits in case user screws up
    if(pwm_out > out_max) {
        pwm_out = out_max;
    }
    else if(pwm_out < out_min) {
        pwm_out = out_min;
    }

    // Write to pwm
    pwmWrite(pin, pwm_out);
}

// Get PWM output
int MotorPWM::getPWMOutput() {
    return pwm_out;
}

// Maps (float) from [in_min, in_max] to (int) in [out_min, out_max]
int MotorPWM::mapFloatPWM(float value) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Debug
void MotorPWM::printSettings() {
    // Print PWM period
    Serial.print("period: ");
    Serial.println(period);

    // Print pwm pulse range 
    Serial.print("t_range: ");
    Serial.print(t_min); Serial.print(" ");
    Serial.println(t_max);

    Serial.print("max_duty: ");
    Serial.println(max_duty);

    // Print user defined range
    Serial.print("in_range: ");
    Serial.print(in_min); Serial.print(" ");
    Serial.println(in_max);

    // Output range
    Serial.print("out_range: ");
    Serial.print(out_min); Serial.print(" ");
    Serial.println(out_max);      
}