#ifdef INTEGRATED_SYSTEM

// ROS Libraries
#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

// Libraries
#include "src/RobotBase.h"
#include "src/Stanley.h"
#include "src/Euler.h"
#include "src/PathReader.h"

// Robot
RobotBase robot(MOTOR_SAMPLE_TIME, IMU_RESET_TIME);
//Motor leftMotor(LEFT_MOTOR, MOTOR_SAMPLE_TIME);
//Motor rightMotor(RIGHT_MOTOR, MOTOR_SAMPLE_TIME);

// Odometry
Pose pose;
Euler ode;

// PID the input values to achieve a slower response
// The motor control should have close to optimal response
PID pidV, pidW;

Filter<float> leftFilter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);
Filter<float> rightFilter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);

// ROS stuff
ros::NodeHandle nh;
geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;
char base_link[] = "/base_link";
char odom[] = "/odom";

void setup() {
  // --- MOTOR SETUP ---
  
  robot.leftMotor.setGains(MOTOR_KP, MOTOR_KI, MOTOR_KD);
  robot.rightMotor.setGains(MOTOR_KP, MOTOR_KI, MOTOR_KD);
  robot.leftMotor.setRange(MOTOR_MIN, MOTOR_MAX);
  robot.rightMotor.setRange(MOTOR_MIN, MOTOR_MAX);
  robot.leftMotor.setIMax(MOTOR_IMAX);
  robot.rightMotor.setIMax(MOTOR_IMAX);

  robot.leftMotor.enc._filter = leftFilter;
  robot.rightMotor.enc._filter = rightFilter;

  robot.begin();

  
  NeoSerial.begin(115200);

  // Serial debug
  #ifdef DEBUG
    debugSerial.println(F("Starting program"));
  #endif

  // Flush buffer
  //while(NeoSerial.available()) NeoSerial.read();

  // Led debug
  pinMode(EMERGENCY_STOP_PIN, INPUT);

  // Setup PID for v and w
  pidV = PID(PID_V_KP, PID_V_KI, PID_V_KD, PID_V_MIN, PID_V_MAX, PID_V_IMAX);
  pidW = PID(PID_W_KP, PID_W_KI, PID_W_KD, PID_W_MIN, PID_W_MAX, PID_W_IMAX);

  // Setup robot
  robot.begin();
  robot.setSpeed(0, 0);

  pinMode(EMERGENCY_HANDSHAKE, OUTPUT);

  // ROS stuff
  nh.initNode();
  broadcaster.init(nh);
}

// State machine for motor controllers
uint8_t stateTrack, statePoseSend;

float vInput = 0.0;
float wInput = 0.0;
float vDesired = 0.0;
float wDesired = 0.0;

String inString[2] = {""};
bool updateControl = true;

void loop() {
  
  static uint32_t sampleLast = millis();
  // Update pose and control speed
  
  if(robot.sampleData()) {
    // Control speed
    robot.drive();

    #ifdef DEBUG  // Print data
      logTime();
    #endif

    // ROS publish data
    t.header.frame_id = odom;
    t.child_frame_id = base_link;
    
    t.transform.translation.x = x;
    t.transform.translation.y = y;
    
    t.transform.rotation = tf::createQuaternionFromYaw(theta);
    t.header.stamp = nh.now();
    
    broadcaster.sendTransform(t);
    nh.spinOnce();

    updateControl = true;
  }
  
  int joystickX = analogRead(PIN_JOYSTICK_X);
  int joystickY = analogRead(PIN_JOYSTICK_Y);

  // vInput = nucVel
  // wInput = nucSteer
  // if (analogRead(joystickX outside dead zone) {
  //  vInput = mapJoystick(joystickX, 499, LINEAR_VELOCITY_MAX, LINEAR_VELOCITY_MIN)
  // }
  // etc. same for wInput

  vInput = mapJoystick(joystickX, 499, LINEAR_VELOCITY_MAX, LINEAR_VELOCITY_MIN);
  wInput = mapJoystick(joystickY, 522, ANGULAR_VELOCITY_MAX, ANGULAR_VELOCITY_MIN);

  // Update control signals
  if(updateControl) {
    // Run controller based on inputs
    vDesired += pidV.pid(vInput-vDesired);
    wDesired += pidW.pid(wInput-wDesired);
    
    // Set speed inputs
    if (digitalRead(EMERGENCY_STOP_PIN)) {
      robot.setSpeed(vDesired, wDesired);
    }
    
    updateControl = false;
  }

  if (digitalRead(EMERGENCY_STOP_PIN) == LOW) {
    // Active signal; return handshake
    digitalWrite(EMERGENCY_HANDSHAKE, HIGH);
    vInput = 0;
    wInput = 0;
    vDesired = 0;
    wDesired = 0;
    robot.setSpeed(0,0);
    robot.brake();
  } else {
    // turn off handshake
    digitalWrite(EMERGENCY_HANDSHAKE, LOW);
  }

  // Obtaining actual data from the robot
    float actualVel =  robot.getVcm();             // m/s
    float actualW = robot.getWcm();             // rad/s
    float actualHeading = robot.getYaw();             // rad
    
    pose = ode.integrate(robot.getVcm(), robot.getYaw(), robot.getDeltaTime());
}

// Prints data
void printData() {
  logTime();
  debugSerial.println();  
}

float mapJoystick(int input, int deadzone, const float& maxVal, const float& minVal) {
  float output;
  if (input >= deadzone) {
    output = (float) (input - deadzone) / (JOYSTICK_MAX - deadzone) * maxVal;
  } else {
    output = (float) (deadzone - input) / (deadzone - JOYSTICK_MIN) * minVal;
  }
  return output;
}

#endif
