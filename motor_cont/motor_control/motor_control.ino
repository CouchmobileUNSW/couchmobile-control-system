#include <Servo.h>
#include "pid.h"

// Motor pins
#define Left1   3
#define Left2   5
#define Right1  9
#define Right2  10

// Encoder pins and defines
#define encoderLeftPinA 2
#define encoderLeftPinB 3
#define encoderLeftPinC 4
#define readA bitRead(PIND,2)
#define readB bitRead(PIND,3)
#define readC bitRead(PIND,4)
// TODO - Add the second encoder

// Motor variables
Servo motorLeft1;
Servo motorLeft2;
Servo motorRight1;
Servo motorRight2;

// Encoder variables
const int cpr = 200; // counts per revolution
volatile long leftCount = 0, rightCount = 0;
double leftSpeed = 0, rightSpeed = 0; 

// PID controller variables
class pid* controller = NULL;
int dt = 250; // Update every 250ms
int motorSpeedA = 0;
int motorSpeedB = 0;
 
void setup() {
  Serial.begin(9600);
  initMotors();
  initEncoders();
  controller = new pid(dt, 180, 0, 0.1, 0.01, 0.5); //TODO - tune this!
}
 
void loop() {
  long desLeft, desRight; // desired speed of the left and right wheel, from Serial comms
  
  // Get desired speed from serial
  // TODO

  // Convert encoder counts into rps every time interval (in this case it's 250ms)
  noInterrupts();
  leftSpeed = 4*leftCount/cpr;
  leftCount = 0;
  rightSpeed = 4*rightCount/cpr;
  rightCount = 0;
  interrupts();
  
  // Calculate next PWM output
  motorSpeedA += controller->calculate(leftSpeed, desLeft);
  motorSpeedB += controller->calculate(rightSpeed, desRight);

  // Update the PWM for the motors
  motorLeft1.write(motorSpeedA);
  motorLeft2.write(motorSpeedA);
  motorRight1.write(motorSpeedB);
  motorRight2.write(motorSpeedB);

  showResults(desLeft, leftSpeed);
  showResults(desRight, rightSpeed);
}

/*
 * Initialise the motors
 */
void initMotors(){
  motorLeft1.attach(Left1);
  motorLeft2.attach(Left2);
  motorRight1.attach(Right1);
  motorRight1.attach(Right1);
}

/*
 * Initialise the encoders
 */
void initEncoders(){
  // Set up the left encoder
  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);
  pinMode(encoderLeftPinC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), isrLeftA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinB), isrLeftB, CHANGE);

  // Set up the right encoder
  // TODO
}

/*
 * Interrupt service routine for the motor's encoders
 */
void isrLeftA() {
  if(readC) return;
  readA != readB ? leftCount++:leftCount--;
}

void isrLeftB() {
  if(readC) return;
  readA == readB ? leftCount++:leftCount--;  
}

/*
 * Show the results
 */
void showResults(int desiredSpeed, int measuredSpeed){
  Serial.print("Desired speed: ");
  Serial.print(desiredSpeed);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("Measured Speed: ");
  Serial.println(measuredSpeed);
}
