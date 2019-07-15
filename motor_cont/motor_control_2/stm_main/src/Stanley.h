#ifndef STANLEY_H
#define STANLEY_H

#include "Arduino.h"
#include "math.h"
#include "Pose.h"

#define STANLEY_GAIN 1

class Stanley {
private:
    // Stanley parameters
    float K = STANLEY_GAIN;     // control gain
    float e_fa;                 // error in front axle
    float delta;                // control angle

    // Path to follow
    PathData path;

    // Derived values
    float cyaw[MAX_PATH_SIZE];  // tangent of path (from cx, cy)
    int lastTargetIdx;          // index of last target
    int currTargetIdx;          // index of curr target

public:
    // Sets path
    void setPath(const PathData &_path);

    // Gets control effort
    float control(Pose robot);       

    // Helper functions
    void calcTarget(Pose robot);            // finds target
    int findMinDistIndex(float x, float y); // finds idx of closest pt
    int findMinIndex(float *z, int N);      // finds min idx of array
    float normalizeAngle(float angle);      // normalise angle to [-pi, pi]
};

#endif