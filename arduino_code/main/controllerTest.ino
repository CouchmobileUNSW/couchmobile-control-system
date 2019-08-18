/*
 * This is a unit test for controller gains
 * Specify the error (e) inputs using serial
 * Get the control effort (m)
 * Inspect e_history and m_history and see current m
 */


#ifdef CONTROLLER
#include "src/Controller.h"

// Set controller gains
Kp = 0.0;
Ki = 0.0;
Kd = 0.0;

// Set control effort range (saturation limits)
float m_min = -1024;
float m_max = 1024;

// Define controller
Controller G;

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

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
  while(NeoSerial.available() > 0) {
    e = NeoSerial.parseFloat();
    flag = true;
  }

  // Check controller gains are correct
  if(flag) {
    // Get control response
    m = G.getControlEffort(e);

    // Print history
    NeoSerial.println("Printing history:");
    G.printHistory();

    // Print control effort
    NeoSerial.print("e: "); NeoSerial.print(e);
    NeoSerial.print("\tm: "); NeoSerial.print(m);
    NeoSerial.println("\n");
    
    flag = false;
  }
}

#endif
