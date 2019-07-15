/*
 * This is a unit test for controller gains
 * Specify the error (e) inputs using serial
 * Get the control effort (m)
 * Inspect e_history and m_history and see current m
 */


#ifdef CONTROLLER
#include "src/Controller.h"

// Set controller gains
float e_gains[] = {2.0, 1.0};
float m_gains[] = {1, 0.5};

// Set control effort range (saturation limits)
float m_min = -1024;
float m_max = 1024;

// Define controller
Controller G;

void setup() {
  // Start up serial
  Serial.begin(115200);

  // Check controller settings
  G.setGains(e_gains, 2, m_gains, 2);
  G.setRange(m_min, m_max);
  G.printSettings();
}

// Variables to take in Serial inputs
bool flag = false;
float e, m;

void loop() {
  // Take in Serial input if available
  while(Serial.available() > 0) {
    e = Serial.parseFloat();
    flag = true;
  }

  // Check controller gains are correct
  if(flag) {
    // Get control response
    m = G.getControlEffort(e);

    // Print history
    Serial.println("Printing history:");
    G.printHistory();

    // Print control effort
    Serial.print("e: "); Serial.print(e);
    Serial.print("\tm: "); Serial.print(m);
    Serial.println("\n");
    
    flag = false;
  }
}

#endif
