#ifdef MOTOR_LINEAR_SPEED
#define MOTOR_LINEAR_SPEED

#include "src/Motor.h"
#include "src/Filter.h"

// Macros
#define SAMPLE_TIME 24e3
#define PLOTTER
#define ACTIVE_MOTOR leftMotor // leftMotor or rightMotor

// Create motor object
Motor leftMotor(LEFT_MOTOR, SAMPLE_TIME);
//Motor rightMotor(RIGHT_MOTOR, SAMPLE_TIME);

Filter<float> filter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);
Filter<float> encoderFilter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  leftMotor.enc._filter = encoderFilter;
  //rightMotor.enc._filter = encoderFilter;

  leftMotor.setGains(MOTOR_KP, MOTOR_KI, MOTOR_KD);
  leftMotor.setRange(MOTOR_MIN, MOTOR_MAX);
  leftMotor.setIMax(MOTOR_IMAX);

  //rightMotor.setGains(MOTOR_KP, MOTOR_KI, MOTOR_KD);
  //rightMotor.setRange(MOTOR_MIN, MOTOR_MAX);
  //rightMotor.setIMax(MOTOR_IMAX);
  
  leftMotor.begin();
  //rightMotor.begin();

  // Set PWM to middle of input range
  leftMotor.setSpeed(0);
  //rightMotor.setSpeed(0);

}

// Variables to take in Serial inputs
float v_d = 0;          // desired speed (m/s)

void loop() {
  // Update every T time
  bool printNow = false;
  if(leftMotor.sampleData()) {
    leftMotor.controlSpeed();
    printNow = true;
  }

  /*
  if(rightMotor.sampleData()) {
    rightMotor.controlSpeed();
    printNow = true;
  }
  */
  
  if (printNow) {
    printData();
  }
  
  // Take in Serial input if available
  if (NeoSerial.available() > 0) {
    while(NeoSerial.available() > 0) {
      v_d = NeoSerial.parseFloat();
      ACTIVE_MOTOR.setSpeed(v_d);
    }
  }
}

// Prints data
void printData() {
  // Get data
  float t = ACTIVE_MOTOR.getCurrTime();        // microseconds
  float v_a = ACTIVE_MOTOR.getSpeed();         // m/s
  float v_d = ACTIVE_MOTOR.getDesiredSpeed();  // m/s
  float e = ACTIVE_MOTOR.getError();           // m/s

  filter.push(v_a);
  float v_filtered = filter.value();

  // Print data
  #ifndef PLOTTER
    NeoSerial.print("t: "); NeoSerial.print(t);
    NeoSerial.print("  v_a: "); NeoSerial.print(v_a, 5);
    NeoSerial.print("  v_d: "); NeoSerial.print(v_d, 5);
    NeoSerial.print("  e: "); NeoSerial.print(e, 5);
  #endif
  // Plot data
  #ifdef PLOTTER
    NeoSerial.print(v_d, 5); NeoSerial.print(", ");
    NeoSerial.print(v_a, 5); NeoSerial.print(", ");
    NeoSerial.print(v_filtered, 5); NeoSerial.print(", ");
    NeoSerial.print("0, 2");
  #endif
  NeoSerial.println();  
}

#endif
