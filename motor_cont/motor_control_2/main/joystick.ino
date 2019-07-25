/*
 * This is an integration test for the IMU
 * Use SCL = PB6, SDA = PB7
 */

#ifdef JOYSTICK


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

  float xval = mapJoystick(joystickX, 499, LINEAR_VELOCITY_MAX, LINEAR_VELOCITY_MIN);
  float yval = mapJoystick(joystickY, 522, ANGULAR_VELOCITY_MAX, ANGULAR_VELOCITY_MIN);

  NeoSerial.print(joystickX);
  NeoSerial.print(" ");
  NeoSerial.print(joystickY);
  NeoSerial.print(" ");
  NeoSerial.print(xval);
  NeoSerial.print(" ");
  NeoSerial.print(yval);
  NeoSerial.println();
  
}

float mapJoystick(int input, int deadzone, const float& maxVal, const float& minVal) {
  float output;
  if (input >= deadzone) {
    output = (float) (input - deadzone) / (JOYSTICK_MAX - deadzone) * maxVal;
  } else {
    output = (float) (deadzone - input) / (deadzone - JOYSTICK_MIN) * minVal;
  }
  return output;
}

#endif
