#ifdef PCB_TEST

void ledTest(bool printSerial);

void setup() {
  NeoSerial.begin(115200);
  ledTest(true);
}

void loop() {
  
}

void ledTest(bool printSerial) {
  if (printSerial) {
    NeoSerial.println("Starting LED test...");
  }
  
  digitalWrite(PIN_STATUS_SERIAL, LOW);
  digitalWrite(PIN_STATUS_IMU, LOW);
  digitalWrite(PIN_STATUS_ENCODER, LOW);
  digitalWrite(PIN_STATUS_MOTOR1, LOW);
  digitalWrite(PIN_STATUS_MOTOR2, LOW);
  delay(400);
  
  digitalWrite(PIN_STATUS_SERIAL, HIGH);
  delay(400);
  digitalWrite(PIN_STATUS_SERIAL, LOW);
  
  digitalWrite(PIN_STATUS_IMU, HIGH);
  delay(400);
  digitalWrite(PIN_STATUS_IMU, LOW);

  digitalWrite(PIN_STATUS_ENCODER, HIGH);
  delay(400);
  digitalWrite(PIN_STATUS_ENCODER, LOW);

  digitalWrite(PIN_STATUS_MOTOR1, HIGH);
  delay(400);
  digitalWrite(PIN_STATUS_MOTOR1, LOW);

  digitalWrite(PIN_STATUS_MOTOR2, HIGH);
  delay(400);
  digitalWrite(PIN_STATUS_MOTOR2, LOW);

  if (printSerial) {
    NeoSerial.println("Finished LED test.");
  }
}

#endif // PCB_TEST
