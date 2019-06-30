#include <Servo.h>
Servo motor;

#define enA 3
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7
 
int motorSpeedA = 0;
int motorSpeedB = 0;
 
void setup() {
  Serial.begin(9600);
  motor.attach(enA);
  
  //pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
 
void loop() {
    int xAxis = analogRead(A0);
    int yAxis = analogRead(A1);
 
    // values between 470 and 550 are considered centre
    // y < 470: motors go backwards
    // y > 550: motors go forwards

    // motor.write --> 0 <= x <= 180
    // 0 <= x <= 90 --> motor goes forward
    // 90 <= x <= 180 --> motor goes backwards
 
    if(yAxis < 470) {
        // set motor A backward
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        // set motor B backward
        digitalWrite(in3, HIGH);
        digitalWrite(in4,LOW);
        // convert the declining y-axis readings for going backward from 470 to 0 into 
        // 0 to 255 value for PWM signal
        motorSpeedA = map(yAxis,470,0,0,255);
        motorSpeedB = map(yAxis,470,0,0,255);
    }
    else if (yAxis > 550) {
        // Set Motor A forward
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // Set Motor B forward
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        // Convert the increasing Y-axis readings for going forward from 550 to 1023 into
        // 0 to 255 value for the PWM signal for increasing the motor speed
        motorSpeedA = map(yAxis, 550, 1023, 0, 255);
        motorSpeedB = map(yAxis, 550, 1023, 0, 255);
      
      // If joystick stays in middle the motors are not moving
    } else {
        motorSpeedA = 0;
        motorSpeedB = 0;
    
    }
    // x values used for left and right control
    if(xAxis < 470) {
        int xMapped = map(xAxis,470,0,0,255);
        motorSpeedA = motorSpeedA - xMapped;
        motorSpeedB = motorSpeedB + xMapped;
        if(motorSpeedA<0) {
            motorSpeedA = 0;
        } 
        if(motorSpeedB>255) {
            motorSpeedB = 0;
        }
    }
    if (xAxis > 550) {
        // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
        int xMapped = map(xAxis, 550, 1023, 0, 255);
        // Move right - decrease right motor speed, increase left motor speed
        motorSpeedA = motorSpeedA + xMapped;
        motorSpeedB = motorSpeedB - xMapped;
        // Confine the range from 0 to 255
        if (motorSpeedA > 255) {
            motorSpeedA = 255;
        }
        if (motorSpeedB < 0) {
        motorSpeedB = 0;
        }
    }
 
    // at lower speeds the motor can be unable to start and may make a buzzing noise
    // TODO: test minimum value for motors to start moving (here 70 is used)
    if(motorSpeedA<70) {
        motorSpeedA = 0;
    }
    if(motorSpeedB<70) {
        motorSpeedB = 0;
    }
    // send PWM signal to motors
    //analogWrite(enA, motorSpeedA);
    //analogWrite(enB, motorSpeedB);
    // TODO: work out connections for DC motors (and H-bridge) 
    Serial.print(motorSpeedA);
    Serial.print("\t");
    Serial.println(motorSpeedB);
    motor.write(motorSpeedA);
}

