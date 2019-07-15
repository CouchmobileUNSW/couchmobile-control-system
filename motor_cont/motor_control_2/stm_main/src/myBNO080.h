
#ifndef MYBNO080_H
#define MYBNO080_H

#include "Arduino.h"
#include "SparkFun_BNO080_Arduino_Library.h"
#include "Wire.h"
#include "math.h"

// pitch-roll-yaw (angle_x, angle_y, angle_z)

#define RESET_PIN PB5

class myBNO080: public BNO080 {
private:
    // Data sampled using parent class methods
    float pitch, roll, yaw;         // Euler angles: pitch, roll, yaw
    float q[4];                     // Quaternion angles: r, i, j, k

    // Most recent sampled time
    unsigned long lastUpdateTime;   // To reset IMU if inactive for too long
    unsigned int T;                 // update interval (ms)
    unsigned long resetTime;        // reset time (ms);

    // I2C pins for hardware reset
    uint8_t _rst;
public:
    // Define RESET pins
    myBNO080(unsigned int _T, unsigned int _resetTime);

    // Reset IMU and settings
    void begin();
    void reset();
    void hardReset();

    // Updates derived variables
    bool update();                  // Update angles before getting them
    void updateLastTime();          // Update last update time

    // Get data
    float getRoll();
    float getPitch();
    float getYaw();
    unsigned long getLastTime();

    // Get angles in degrees
    float getRollDeg();
    float getPitchDeg();
    float getYawDeg();

    // Quarternion to Euler conversion
    void qToEuler();
};

#endif