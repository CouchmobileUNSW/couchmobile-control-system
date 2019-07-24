/*
 * This is an integration test for the IMU
 * Use SCL = PB6, SDA = PB7
 */

#ifdef JOYSTICK

#define PIN_JOYSTICK_X A5
#define PIN_JOYSTICK_Y A4

#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023

#define JOYSTICK_DEADZONE_X 499
#define JOYSTICK_DEADZONE_Y 522

#define MAX_VAL 1.0
#define MIN_VAL -1.0

void setup() {
  // Start up serial
  NeoSerial.begin(115200);

  // Configure IMU for sample time
  NeoSerial.println("Starting Joystick");
}

void loop() {
  // Sample IMU data if available

  int joystickX = analogRead(PIN_JOYSTICK_X);
  int joystickY = analogRead(PIN_JOYSTICK_Y);

  float xval = mapJoystick(joystickX, 499);
  float yval = mapJoystick(joystickY, 522);

  NeoSerial.print(joystickX);
  NeoSerial.print(" ");
  NeoSerial.print(joystickY);
  NeoSerial.print(" ");
  NeoSerial.print(xval);
  NeoSerial.print(" ");
  NeoSerial.print(yval);
  NeoSerial.println();
  
}

float mapJoystick(int input, int deadzone) {
  float output;
  if (input >= deadzone) {
    output = (float) (input - deadzone) / (JOYSTICK_MAX - deadzone) * MAX_VAL;
  } else {
    output = (float) (deadzone - input) / (deadzone - JOYSTICK_MIN) * MIN_VAL;
  }
  return output;
}

#endif
