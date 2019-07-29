#ifdef MOTOR_LINEAR_SPEED
#define MOTOR_LINEAR_SPEED

#include "src/Motor.h"
#include "src/Filter.h"

// Macros
#define SAMPLE_TIME 24e3
#define PLOTTER

// Create motor object
Motor leftMotor(LEFT_MOTOR, SAMPLE_TIME);

Filter<float> filter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);
Filter<float> encoderFilter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

  leftMotor.enc._filter = encoderFilter;

  leftMotor.setGains(MOTOR_KP, MOTOR_KI, MOTOR_KD);
  leftMotor.setRange(MOTOR_MIN, MOTOR_MAX);
  leftMotor.setIMax(MOTOR_IMAX);
  // Config motors
  leftMotor.begin();

  // Set PWM to middle of input range
  leftMotor.setSpeed(0);

}

// Variables to take in Serial inputs
float v_d = 0;          // desired speed (m/s)

void loop() {
  // Update every T time
  if(leftMotor.sampleData()) {
    leftMotor.controlSpeed();
    printData();
  }
  
  // Take in Serial input if available
  if (NeoSerial.available() > 0) {
    while(NeoSerial.available() > 0) {
      v_d = NeoSerial.parseFloat();
      leftMotor.setSpeed(v_d);
    }
  }
}

// Prints data
void printData() {
  // Get data
  float t = leftMotor.getCurrTime();        // microseconds
  float v_a = leftMotor.getSpeed();         // m/s
  float v_d = leftMotor.getDesiredSpeed();  // m/s
  float e = leftMotor.getError();           // m/s

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
