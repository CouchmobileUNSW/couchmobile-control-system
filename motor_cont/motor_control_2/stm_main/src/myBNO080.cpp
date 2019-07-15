
#include "myBNO080.h"

// Define RESET and INTERRUPT pins
myBNO080::myBNO080(unsigned int _T, unsigned int _resetTime) 
    : _rst(RESET_PIN), T(_T), resetTime(_resetTime) {
}

// Configure IMU and settings
void myBNO080::begin() {
    // Perform a hard reset
    hardReset();

    // Configure settings
    reset();
}

// Sets up the IMU
void myBNO080::reset() {
    // Start I2C protocol
    Wire.begin();
    Wire.setClock(400000); //Increase I2C data rate to 400kHz
    BNO080::begin();

    // Enable measurements every T ms
    enableGameRotationVector(T);  // Send data update every T ms
    enableAccelerometer(T);
    updateLastTime();
 }

// Hard resets the IMU
void myBNO080::hardReset() {
    // Initialise pins
    pinMode(_rst, OUTPUT);

    // Reset IMU
    digitalWrite(_rst, LOW);

    // Delay so it can register
    delay(5);

    // Turn it back on
    digitalWrite(_rst, HIGH);
}

// Getters
float myBNO080::getRoll() {
    return roll;
}

float myBNO080::getPitch() {
    return pitch;
}

float myBNO080::getYaw() {
    return yaw;
}

unsigned long myBNO080::getLastTime() {
    return lastUpdateTime;
}

// Update derived variables based off sampled data (parent class)
// Need to call dataAvailable() to update the sampled data
bool myBNO080::update() {
    if(dataAvailable() > 0) {
        // Update time
        updateLastTime();

        // Calculate quaternions
        q[1] = getQuatI();
        q[2] = getQuatJ();
        q[3] = getQuatK();
        q[0] = getQuatReal();

        // Convert quaternions to euler angles
        qToEuler();
        return true;
    }
    else if(micros() - lastUpdateTime >= resetTime*1e3){
        //Serial.println("Reset IMU");
        reset();
    }
    return false;
}

// Update last update time
void myBNO080::updateLastTime() {
    lastUpdateTime = micros();
}

// Quarternion to Euler conversion
void myBNO080::qToEuler() {
    roll = -atan2(2 * q[1] * q[3] + 2 * q[2] * q[0], 1 - 2 * q[1]*q[1] - 2 * q[2] * q[2]);
    pitch = asin(2 * q[2] * q[3] - 2 * q[1] * q[0]); 
    yaw = -atan2(2 * q[1] * q[2] + 2 * q[3] * q[0], 1 - 2 * q[2] * q[2] - 2 * q[3] * q[3]);
}

// Get angles in degrees
float myBNO080::getRollDeg() {
    return roll * 180/PI;
}

float myBNO080::getPitchDeg() {
    return pitch * 180/PI;
}

float myBNO080::getYawDeg() {
    return yaw * 180/PI;
}
