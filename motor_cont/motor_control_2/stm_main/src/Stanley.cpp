#include "Stanley.h"

// Sets path
void Stanley::setPath(const PathData &_path) {
    memcpy(&path, &_path, sizeof(PathData));

    // Determine cyaw (back difference)
    Serial.print("c_yaw: ");
    for(int i = 0; i < path.N; i++) {
        cyaw[i] = atan2(path.cy[i+1] - path.cy[i],
                        path.cx[i+1] - path.cx[i]);
        Serial.print(cyaw[i]*180/PI); Serial.print(", ");
    }
    // Set last index
    cyaw[path.N-1] = cyaw[path.N-2];
    Serial.println();

    lastTargetIdx = currTargetIdx = 0;
}

// Gets control effort
float Stanley::control(Pose robot) {
    // Find the target and update e_fa
    calcTarget(robot);

    // theta_e corrects the heading error
    float theta_e = normalizeAngle(cyaw[currTargetIdx] - robot.yaw);

    // theta_d corrects the cross track error
    float theta_d = atan2(K * e_fa, robot.v);

    // Steering control
    delta = theta_e + theta_d;

    // Serial.print("ind: "); Serial.println(currTargetIdx, 5);
    // Serial.print("cyaw: "); Serial.println(cyaw[currTargetIdx], 5);
    // Serial.print("robot.yaw: "); Serial.println(robot.yaw, 5);
    // Serial.print("theta_e: "); Serial.println(theta_e, 5);
    // Serial.print("K: "); Serial.println(K, 5);
    // Serial.print("e_fa: "); Serial.println(e_fa, 5);
    // Serial.print("v: "); Serial.println(robot.v, 5);
    // Serial.print("theta_d: "); Serial.println(theta_d, 5);
    // Serial.print("delta: "); Serial.println(delta, 5);
    // Serial.println();
    return delta;
}

// Gets target index
void Stanley::calcTarget(Pose robot) {
    // Calculate front axle position

    // Search nearest point index
    lastTargetIdx = currTargetIdx;
    currTargetIdx = findMinDistIndex(robot.x, robot.y);

    // Ensure we always move forwards
    if(lastTargetIdx > currTargetIdx) {
        currTargetIdx = lastTargetIdx;
    }

    // Project RMS error onto the front axle vector
    float dx = path.cx[currTargetIdx] - robot.x;
    float dy = path.cy[currTargetIdx] - robot.y;

    e_fa = dx * (cos(robot.yaw + PI/2)) + dy * (sin(robot.yaw + PI/2));
}

// Finds the index of the closest point on path
int Stanley::findMinDistIndex(float x, float y) {
    // Array to store square of distances
    float d[MAX_PATH_SIZE];

    // Find square of distances
    for(int i = 0; i < path.N; i++) {
        d[i] = sq(path.cx[i] - x) +
                sq(path.cy[i] - y);
    }

    // Find minimum index
    return findMinIndex(d, path.N);
}

// Find min index
int Stanley::findMinIndex(float *z, int N){
    int minInd = 0;
    for(int i = 0; i < N; i++) {
        if(z[i] < z[minInd]) minInd = i;
    }
    return minInd;
}

// Normalise angle to [-pi, pi]
float Stanley::normalizeAngle(float angle) {
    while(angle > PI) {
        angle -= 2*PI;
    }
    while(angle < -PI) {
        angle += 2*PI;
    }
    return angle;
}
