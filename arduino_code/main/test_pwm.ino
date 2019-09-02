#ifdef PWM_TEST
#include "src/MotorPWM.h"
#include "src/Config.h"
#include "src/MotorBase.h"


#include "src/Motor.h"
#include "src/Filter.h"

// Macros
#define SAMPLE_TIME 24e3
#define PLOTTER

MotorPWM pwm(6);

Filter<float> filter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);
Filter<float> encoderFilter(ENCODER_FILTER_COEFFICIENTS, ENCODER_FILTER_SIZE);

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

    pwm.setInputPulse(3000, 1000, 2000);
    pwm.setRange(-1024, 1024);
    pwm.begin();
}

// Variables to take in Serial inputs
float v_d = 0;          // -1024 -> +1024

void loop() {
  
  
  printData();
  // Take in Serial input if available
  if (NeoSerial.available() > 0) {
    while(NeoSerial.available() > 0) {
      v_d = NeoSerial.parseFloat();
    }
  }
  pwm.writeValue(v_d);
  delay(100);
}

// Prints data
void printData() {
  NeoSerial.print(pwm.getPWMOutput());
  NeoSerial.println();  
}

#endif
