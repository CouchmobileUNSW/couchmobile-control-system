#include <Servo.h>

// Motor pins and variables
#define Left1   3
Servo motorLeft1;
int motorSpeedA = 0;

// Encoder pins and defines
#define encoderLeftPinA 2
#define encoderLeftPinB 3
#define encoderLeftPinC 4
#define readA bitRead(PIND,2)
#define readB bitRead(PIND,3)
#define readC bitRead(PIND,4)

// Encoder variables
const int cpr = 200; // counts per revolution
volatile long leftCount = 0;
double leftSpeed = 0;
 
void setup() {
  Serial.begin(9600);
  motorLeft1.attach(Left1);
  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);
  pinMode(encoderLeftPinC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), isrLeftA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinB), isrLeftB, CHANGE);
}
 
void loop() {
  // Convert encoder counts into rps every time interval (in this case it's 250ms)
  noInterrupts();
  leftSpeed = 4*leftCount/cpr;
  leftCount = 0;
  interrupts();

  motorLeft1.write(180);

  showResults(180, leftSpeed);

  delay(250);
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
