#ifndef POSE_H
#define POSE_H

#define MAX_PATH_SIZE 200

// Position of the car
typedef struct pose {
    float x;
    float y;
    float yaw;
    float v;
} Pose;

// Path to follow
typedef struct pathData {
    uint8_t N;                  // Number of values
    float cx[MAX_PATH_SIZE];    // x array of path
    float cy[MAX_PATH_SIZE];    // y array of path
} PathData;
#endif