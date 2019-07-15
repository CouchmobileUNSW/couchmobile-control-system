
#include "HardwareEncoder.h"

// Constructor - define the timer number
HardwareEncoder::HardwareEncoder(uint8_t _timer_num)
  : timer_num(_timer_num), timer(timer_num) {
}

// Initialise the hardware encoder
void HardwareEncoder::begin() {
  // Set pins to input and enable pullup resistors
  pinMode(pinA[timer_num], INPUT_PULLUP);
  pinMode(pinB[timer_num], INPUT_PULLUP);

  // Set up timer
  timer.setMode(0, TIMER_ENCODER);          // set to encoder mode, channel not used in this mode
  timer.pause();                            // pause timer while configuring
  timer.setPrescaleFactor(1);               // have lowest prescaler, so max tick resolution
  timer.setOverflow(OVERFLOW);              // overflow value
  timer.setCount(0);                        // reset encoder counter
  timer.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); // use both channels edge changes
  timer.refresh();                          // Refresh the timer's count, prescale, and overflow
  timer.resume();                           // start the encoder
}

// Read encoder values
int HardwareEncoder::sampleTicks() {
  return timer.getCount();
}

// Resets encoder ticks
void HardwareEncoder::resetTicks() {
  timer.pause();
  timer.setCount(0);
  timer.resume();
}



