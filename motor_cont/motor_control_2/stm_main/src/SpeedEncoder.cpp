#include "SpeedEncoder.h"

// Define timer number, tick ratio, sample time
SpeedEncoder::SpeedEncoder(uint8_t timer_num, unsigned int _tickRatio, unsigned int _T) 
    : enc(timer_num), tickRatio(_tickRatio), T(_T) {
}

// Initialise the speed encoder
void SpeedEncoder::begin() {
    enc.begin();
}

// Sample the encoder speed at T
// Returns true if data is sampled/updated
bool SpeedEncoder::sampleData() {
    if(micros() - currTime >= T) {
        // Update ticks
        prevTicks = currTicks;
        currTicks = enc.sampleTicks();

        // Update time
        prevTime = currTime;
        currTime = micros();

        // Calculate speed
        calculateSpeed();

        return true;
    }
    return false;
}

// Get encoder speed in COUNTS/S
float SpeedEncoder::getTickSpeed() {
    return tickSpeed;
}

// Get encoder speed in RAD/S
float SpeedEncoder::getRadianSpeed() {
    return ticksToRad(tickSpeed);
}

// Gets latest sample time
unsigned long SpeedEncoder::getCurrTime() {
    return currTime;
}

// Gets difference in sample times
unsigned long SpeedEncoder::getDeltaTime() {
    return currTime-prevTime;
}

// Get current ticks
int SpeedEncoder::getCurrTicks() {
    return currTicks;
}

// Get prev ticks
int SpeedEncoder::getPrevTicks() {
    return prevTicks;
}

// Gets difference in ticks
int SpeedEncoder::getDeltaTicks() {
    return currTicks-prevTicks; 
}

// Calculates speed using current sample data
void SpeedEncoder::calculateSpeed() {
    // Calculate dTicks first
    tickSpeed = (float) currTicks - prevTicks;

    // CASE 1: underflow --> add overflow amount
    if(tickSpeed <= -OVERFLOW/2) {
        tickSpeed += OVERFLOW + 1;
    }
    // CASE 2: overflow --> subtract overflow difference
    else if(tickSpeed >= OVERFLOW/2) {
        tickSpeed -= OVERFLOW + 1;
    }

    // Calculate speed
    tickSpeed = 1e6*tickSpeed/(currTime-prevTime);
}

// Conversion functions
float SpeedEncoder::ticksToRad(float w_ticks) {
    return (float)tickSpeed * 2*PI/tickRatio;
}

float SpeedEncoder::radToTicks(float w_rad) {
    return (float)tickSpeed * tickRatio/(2*PI);
}

// Debug
void SpeedEncoder::printData() {
    // Print ticks
    Serial.print("ticks: ");
    Serial.print(prevTicks); Serial.print(", ");
    Serial.print(currTicks);

    // Print times
    Serial.print("\ttime: ");
    Serial.print(prevTime); Serial.print(", ");
    Serial.print(currTime);

    // Print speed
    Serial.print("\tSpeed: ");
    Serial.println(tickSpeed);
}


