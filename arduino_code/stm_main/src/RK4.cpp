#include "RK4.h"

// Sets state
void RK4::setState(Pose state) {
    memcpy(&pose, &state, sizeof(Pose));
}

// Integrates ODE [x, y, angle]
Pose RK4::integrate(float v, float angle, float dt) {
    // Find w from measured angle (for rk4)
    float w = (angle - pose.yaw)/dt;

    // Weights
    float k00 = v * cos(pose.yaw);
    float k01 = v * sin(pose.yaw);
    float k02 = w;

    float k10 = v * cos(pose.yaw + dt/2 * k02);
    float k11 = v * sin(pose.yaw + dt/2 * k02);
    float k12 = w;

    float k20 = v * cos(pose.yaw + dt/2 * k12);
    float k21 = v * sin(pose.yaw + dt/2 * k12);
    float k22 = w; 

    float k30 = v * cos(pose.yaw + dt * k22);
    float k31 = v * sin(pose.yaw + dt * k22);
    float k32 = w;

    // Calculate new pose
    pose.x += dt/6 * (k00 + 2*(k10 + k20) + k30);
    pose.y += dt/6 * (k01 + 2*(k11 + k21) + k31);
    pose.yaw = angle;
    pose.v = v;

    return pose;
}



