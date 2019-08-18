#ifndef SPEED_ENCODER_H
#define SPEED_ENCODER_H

#include "Arduino.h"
#include "HardwareEncoder.h"
#include "math.h"

/* SpeedEncoder class to measure the speed of an encoder
    - Ticks are SAMPLED using the HardwareEncoder class
*/ 
class SpeedEncoder {
private:
    // Tick samples to get speed
    int prevTicks;
    int currTicks;

    // Tick sample times
    unsigned long prevTime;     // microseconds
    unsigned long currTime;     // microseconds
    unsigned long T;            // microseconds

    // Hardware encoder object
    HardwareEncoder enc;

    // Speed
    float tickSpeed;            // counts/s
    unsigned int tickRatio;     // counts/rev

public:
    // Config
    SpeedEncoder(uint8_t timer_num, unsigned int _tickRatio, unsigned int _T);
    void begin();

    // Encoder data
    bool sampleData();              // samples data - updates variables
    float getTickSpeed();           // counts/s
    float getRadianSpeed();         // rad/s
    unsigned long getDeltaTime();   // microseconds
    unsigned long getCurrTime();    // microseconds


    // Debug variables
    int getCurrTicks();            // count/s
    int getPrevTicks();            // counts/s
    int getDeltaTicks();           // count/s

    // Helper functions
    void calculateSpeed();
    float ticksToRad(float w_ticks);
    float radToTicks(float w_rad);

    // Debug
    void printData();
};

#endif