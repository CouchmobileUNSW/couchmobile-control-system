#ifndef RK4_H
#define RK4_H

// NOTE: angle MUST BE IN RADIANS!!!!

#include "Arduino.h"
#include "math.h"
#include "Pose.h"

class RK4 {
private:
    // Variable
    Pose pose;

public:
    // Sets state
    void setState(Pose state);

    // Integrate
    Pose integrate(float v, float angle, float dt);
};

#endif