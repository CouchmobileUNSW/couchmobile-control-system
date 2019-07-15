#include "Euler.h"

// Sets state
void Euler::setState(Pose state) {
    memcpy(&pose, &state, sizeof(Pose));
}

// Integrates ODE
Pose Euler::integrate(float v, float angle, float dt) {
    // Integrate [x, y, angle]
    pose.x += dt*v*cos(angle);     // x
    pose.y += dt*v*sin(angle);     // y
    pose.yaw = angle;              // angle
    pose.v = v;
    return pose;
}



