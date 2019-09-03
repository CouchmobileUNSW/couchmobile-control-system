// Pin connections list as defined on PCB
/*  MEGA pins
 *   
 * A4   - Joystick Y
 * A5   - Joystick X
 * A14  - E-stop input pin
 * A15  - E-stop handshake
 * 
 * D6   - LEFT_MOTOR_PWM      // Defined in config.h
 * D7   - RIGHT_MOTOR_PWM     // Defined in config.h
 * D2   - ENCODER_1_A         // Defined in Encoder.cpp
 * D18  - ENCODER_1_B         // Defined in Encoder.cpp
 * D3   - ENCODER_2_A         // Defined in Encoder.cpp
 * D19  - ENCODER_2_B         // Defined in Encoder.cpp
 * 
 * D22  - STATUS_SERIAL
 * D23  - STATUS_IMU
 * D24  - STATUS_ENCODER
 * D25  - STATUS_M1
 * D26  - STATUS_M2
 * 
 * D20  - i2c SDA
 * D21  - i2c SCL
 */

/*  How to use:
 * 
 *  Comment out the #defines that are not used; and only uncoment the #define for the module you want to use
 *  
 *  Integrated system is the entire system. The rest are debug functions and testing functions.
 * 
 */

// Pin connections as defined in Arduino software
// EMERGENCY STOP
#define EMERGENCY_STOP_PIN A14
#define EMERGENCY_HANDSHAKE A15

#define PIN_JOYSTICK_X A5
#define PIN_JOYSTICK_Y A4

#define PIN_STATUS_SERIAL 22
#define PIN_STATUS_IMU 23
#define PIN_STATUS_ENCODER 24
#define PIN_STATUS_MOTOR1 25 
#define PIN_STATUS_MOTOR2 26

#define PIN_I2C_SDA 20
#define PIN_I2C_SCL 21

// Unit tests
//#define IMU
//#define ENCODER
//#define SPEED_ENCODER
//#define PWM_TEST
//#define CONTROLLER
//#define JOYSTICK
//#define PCB_TEST

// Single motor integration tests
//#define CALIBRATE
//#define MOTOR_IDENTIFY  // motors with no controller
//#define MOTOR_IDENTIFY_2  // motors with no controller
//#define MOTOR_INTEGRATED  // motors with controller
//#define MOTOR_LINEAR_SPEED  // motors in m/s

// Combined motor integration tests
//#define ROBOT_DRIVER  // drives robot using v and w

// Odometry tests
//#define ODOMETRY // finds the position of the robot

// Path tracking tests
//#define STANLEY_SIMULATION
//#define STANLEY

// Serial tests
//#define NUC_SERIAL

// Integrated code
#define INTEGRATED_SYSTEM

// Debug statements
//#define DEBUG

// ----Benchmark function----
// Log time between next occurence
//#include <NeoHWSerial.h>
void logTime() {
  static uint32_t prevTime, currTime;
  prevTime = currTime;
  currTime = micros();
  //NeoSerial.println(currTime-prevTime);
}

// --- PARAMETERS ---

#define LINEAR_VELOCITY_MAX 0.5
#define LINEAR_VELOCITY_MIN -0.5

#define ANGULAR_VELOCITY_MAX 1.0
#define ANGULAR_VELOCITY_MIN -1.0

// >> PIDV Parameters; They set the response time to a desired linear velocity
// PID gain values
#define PID_V_KP    0.4
#define PID_V_KI    0.03
#define PID_V_KD    0.000

// PID output saturation values
#define PID_V_MIN   -1.0
#define PID_V_MAX   1.0

// PID integral windup saturation value
#define PID_V_IMAX  0.0

// >> PIDW Parameters; They set the response time to a desired angular velocity
// PID gain values
#define PID_W_KP    0.3
#define PID_W_KI    0.04
#define PID_W_KD    0.0

// PID output saturation values
#define PID_W_MIN   -2.0
#define PID_W_MAX   2.0



// PID integral windup saturation value
#define PID_W_IMAX  0.0

// >> Motor parameters; They set the response time of the motor

#define MOTOR_SAMPLE_TIME 24e3 // microseconds

// Units are PWM scale units. -1024 = Max backwards; 1024 = Max forwards
// PID gain values
#define MOTOR_KP    30

#define MOTOR_KI    40
#define MOTOR_KD    0.5

// PID saturation values
#define MOTOR_MIN   -1024
#define MOTOR_MAX   1024

// PID integral windup saturation value
#define MOTOR_IMAX  50

// --- ENCODER FILTER ---

const int ENCODER_FILTER_SIZE = 3;
const float ENCODER_FILTER_COEFFICIENTS[ENCODER_FILTER_SIZE] = {
  0.500,
  0.333,
  0.167
};

// --- IMU PARAMETERS ---
#define IMU_RESET_TIME -1 // microseconds; -1 = inf

// --- JOYSTICK PARAMETERS ---

#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023

#define JOYSTICK_DEADZONE_X 499
#define JOYSTICK_DEADZONE_Y 522
