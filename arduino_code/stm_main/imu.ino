/*
 * This is an integration test for the IMU
 * Use SCL = PB6, SDA = PB7
 */

#ifdef IMU

#include "src/myBNO080.h"
#include <libmaple/iwdg.h>

// Timing macros
#define IMU_SAMPLE_TIME 5   // milliseconds
#define IMU_RESET_TIME 50   // milliseconds
#define WATCHDOG_TIME 500   // milliseconds
#define iwdg_init_ms(N) iwdg_init(IWDG_PRE_256,((N)/5)) // NOTE: watchdog is not that accurate: 6.4ms

// Create IMU object
myBNO080 myIMU(IMU_SAMPLE_TIME, IMU_RESET_TIME);

void setup() {
  // Start up serial
  Serial.begin(115200);

  // Initialise watchdog
  iwdg_init_ms(WATCHDOG_TIME);

  // Configure IMU for sample time
  Serial.println("Starting IMU");
  myIMU.begin();

  // Print out settings
  Serial.println("Rotation vector, accelerometer, enabled");
  Serial.println("Output in form i, j, k, real, accuracy");  
}

void loop() {
  // Sample IMU data if available
  if(myIMU.update()) {
    printData();
  }

  // Reset watchdog
  iwdg_feed();
}

// Prints data
void printData() {
  Serial.print(myIMU.getLastTime());
  Serial.print(", ");
  Serial.print(myIMU.getPitchDeg());
  Serial.print(", ");
  Serial.print(myIMU.getRollDeg());
  Serial.print(", ");
  Serial.print(myIMU.getYawDeg());
  Serial.print(", ");
  Serial.print(myIMU.getQuatRadianAccuracy());
  Serial.println();  
}

#endif
