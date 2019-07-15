/*
  Written by Matthew Vong
  Use:  counts the ticks of a quadrature encoder using the STM32 hardware
        timer/encoder interrupt
  NOTE:
    - this is does not deal with encoder overflow
    - do NOT use this if your sample time is too low or if your speed is too high
    - You should implement a hardware debounce using a capacitor
*/
#ifndef HARDWARE_ENCODER_H
#define HARDWARE_ENCODER_H

#include "Arduino.h"
#include "HardwareTimer.h"

#define QUAD_TIMER_1 1
#define QUAD_TIMER_2 2
#define QUAD_TIMER_3 3
#define QUAD_TIMER_4 4

// Overflow value
#define OVERFLOW 65535

// Define pin numbers associated to each timer
static byte pinA[5] = {0, PA8, PA0, PA6, PB6};
static byte pinB[5] = {0, PA9, PA1, PA7, PB7};

class HardwareEncoder {
private:
  // Timer number
  uint8_t timer_num;

  // Hardware timer object
  HardwareTimer timer;

public:
  // Constructor - define the timer number
  HardwareEncoder(uint8_t timer_num);

  // Initialise the hardware encoder
  void begin();

  // Read encoder values
  int sampleTicks();

  // Resets encoder ticks
  void resetTicks();
};

#endif
