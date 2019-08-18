
#ifdef ENCODER_HARDWARE

#include "src/HardwareEncoder.h"

/*
 * For this project TIMER4 is used for PWM
 * Use TIMER2 and TIMER3 for encoders
 */

// Create HardwareEncoder objects
HardwareEncoder leftEncoder(QUAD_TIMER_2);
HardwareEncoder rightEncoder(QUAD_TIMER_3);

void setup() {
  // Start up serial
  Serial.begin(115200);

  // Config encoders
  leftEncoder.begin();
  rightEncoder.begin();
}

void loop() {
  // Print ticks
  Serial.print("left/right: "); 
  Serial.print(leftEncoder.sampleTicks());
  Serial.print(" "); 
  Serial.print(rightEncoder.sampleTicks());
  Serial.println();

  // Type something into serial to reset ticks
  while(Serial.available() > 0) {
    // Flush buffer
    Serial.read();

    // Reset encoders
    leftEncoder.resetTicks();
    rightEncoder.resetTicks();
  }
}

#endif
