/*
 * This is a speed unit test for the STM32F103
 * Specify the tickRatio, SAMPLE_TIME and QUAD_TIMER_x (timers with encoder mode)
 * See the "SpeedEncoder.h" file for the pinouts for each quadrature encoder timer
*/
#ifdef SPEED

#include "src/SpeedEncoder.h"

#define tickRatio 1920
#define SAMPLE_TIME 8e3   // microseconds

SpeedEncoder leftEncoder(QUAD_TIMER_2, tickRatio, SAMPLE_TIME);

void setup() {
  // Start up serial
  Serial.begin(115200);

  // Config encoders
  leftEncoder.begin();
}

void loop() {
  // Update every SAMPLE_TIME
  if(leftEncoder.sampleData()) {
    printData();
  }
}

// Prints data
void printData() {
  // Get data
  float w = leftEncoder.getTickSpeed();
  float t = leftEncoder.getCurrTime();

  // Print details
  Serial.print(t); Serial.print(", ");
  Serial.print(w); Serial.println();  
}

#endif
