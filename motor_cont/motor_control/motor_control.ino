#include "Arduino.h" 
#include <Servo.h>

// Controller struct
struct pid{
    double dt;
    double max;
    double min;
    double Kp;
    double Kd;
    double Ki;
    double error;
    double integral;
};

struct pid* con;

// Encoder variables
#define encoderPinA 2
#define encoderPinB 3
#define encoderPinC 4
#define readA bitRead(PIND,2)
#define readB bitRead(PIND,3)
#define readC bitRead(PIND,4)

volatile long encoderCounts = 0;
unsigned long start;
const int cpr = 200;
int measuredSpeed = 0; 

// Motor variables
#define motorPin 9
volatile long val;
volatile long desiredSpeed;
Servo motor;  // create servo object for the PWM
 
void setup()
{
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(encoderPinB, INPUT_PULLUP);      // sets pin B as input
  pinMode(encoderPinC, INPUT_PULLUP);      // sets pin C as input

  // Attach pins to encoder interrupt function
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);

  motor.attach(motorPin);  // attach the motor to pin 9 for PWM

  // Initialise the controller struct
  con = malloc(sizeof(struct pid));
  con->dt = 0.1;
  con->max = 100;
  con->min = -100;
  con->Kp = 0.1;
  con->Kd = 0.01;
  con->Ki = 0.5;
  con->error = 0;
  con->integral = 0;
}
 
void loop()
{
  desiredSpeed = 5; // Set this to 5m/s for now

  // Update rps (measuredSpeed) every second
  if(millis() - start > 1000) {
    start = millis();
    noInterrupts();
    measuredSpeed = encoderCounts/cpr;
    encoderCounts = 0;
    interrupts();
  }
  
  // Calculate next desired output
  val = calculatePID(con, measuredSpeed, desiredSpeed) + measuredSpeed;
  motor.write(val);

  // Print the results
  Serial.print("Desired speed: ");
  Serial.print(desiredSpeed);
  Serial.print("m/s\t");
  Serial.print("\t");
  Serial.print("Current count: ");
  Serial.print(encoderCounts);
  Serial.println("m/s");
 
  delay(20);
}
 
// Interrupt service routine for the motor's encoder
void isrA() {
  if(readC) return;
  readA != readB ? encoderCounts++:encoderCounts--;
}

void isrB() {
  if(readC) return;
  readA == readB ? encoderCounts++:encoderCounts--;  
}

// PID controller
double calculatePID(struct pid* controller, double measured, double predicted){
    double error = measured - predicted;
    double Pout = controller->Kp * error;
    
    controller->integral += error * controller->dt;
    double Iout = controller->Ki * controller->integral;

    double derivative = (error - controller->error) / controller->dt;
    double Dout = controller->Kd * derivative;

    double output = Pout + Iout + Dout;
    printf("output: %f\n", output);

    if(output > controller->max)
        output = controller->max;
    if(output < controller->min)
        output = controller->min;

    controller->error = error;

    return output;
}
