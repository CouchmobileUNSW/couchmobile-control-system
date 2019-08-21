#ifdef PCB_TEST

/*
 * Functions for checking whether or not the functionality provided by the PCB works.
 * 
 * Written by: William Chen
 * Date: 19/08/2019
 */

void ledTest(bool printSerial, int ledDelay);
void i2cLogicConverterTest(bool printSerial, int delayMs);
void estopTest(bool printSerial, int delayMs);
void estopHSTest(bool printSerial, int delayMs);

void setup() {
  NeoSerial.begin(115200);
  // ledTest(true, 1000);
  pinMode(PIN_I2C_SDA, OUTPUT);
  pinMode(PIN_I2C_SCL, OUTPUT);
  pinMode(EMERGENCY_HANDSHAKE, OUTPUT);

}

void loop() {
  //i2cLogicConverterTest(true, 1000);
  estopHSTest(true, 10000);
}

void ledTest(bool printSerial, int ledDelay) {
  if (printSerial) {
    NeoSerial.println("Starting LED test...");
  }
  
  digitalWrite(PIN_STATUS_SERIAL, LOW);
  digitalWrite(PIN_STATUS_IMU, LOW);
  digitalWrite(PIN_STATUS_ENCODER, LOW);
  digitalWrite(PIN_STATUS_MOTOR1, LOW);
  digitalWrite(PIN_STATUS_MOTOR2, LOW);
  delay(ledDelay);
  
  digitalWrite(PIN_STATUS_SERIAL, HIGH);
  delay(ledDelay);
  digitalWrite(PIN_STATUS_SERIAL, LOW);
  
  digitalWrite(PIN_STATUS_IMU, HIGH);
  delay(ledDelay);
  digitalWrite(PIN_STATUS_IMU, LOW);

  digitalWrite(PIN_STATUS_ENCODER, HIGH);
  delay(ledDelay);
  digitalWrite(PIN_STATUS_ENCODER, LOW);

  digitalWrite(PIN_STATUS_MOTOR1, HIGH);
  delay(ledDelay);
  digitalWrite(PIN_STATUS_MOTOR1, LOW);

  digitalWrite(PIN_STATUS_MOTOR2, HIGH);
  delay(ledDelay);
  digitalWrite(PIN_STATUS_MOTOR2, LOW);

  if (printSerial) {
    NeoSerial.println("Finished LED test.");
  }
}

void i2cLogicConverterTest(bool printSerial, int delayMs) {
  if (printSerial) {
    NeoSerial.println("Starting LED test...");
  }

  for (int i = 0; i < 20; i++) {
    if (i % 2 == 0) {
      // Even
      digitalWrite(PIN_I2C_SDA, HIGH);
      digitalWrite(PIN_I2C_SCL, LOW);
      digitalWrite(PIN_STATUS_IMU, HIGH);
    } else {
      // Odd
      digitalWrite(PIN_I2C_SDA, LOW);
      digitalWrite(PIN_I2C_SCL, HIGH);
      digitalWrite(PIN_STATUS_IMU, LOW);
    }
    delay(delayMs);
  }

  if (printSerial) {
    NeoSerial.println("Finished LED test.");
  }
}

void estopTest(bool printSerial, int delayMs) {
  if (printSerial) {
    NeoSerial.println("Starting Estop Test.");
  }
  // Simulate PWM signals through D6 and D7
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  int timeElapsed = 0;
  const int timeInterval = 5;
  while (timeElapsed < delayMs) {
    if (digitalRead(EMERGENCY_STOP_PIN) == LOW) {
      // Turn off
      //digitalWrite(6, 0);
      //digitalWrite(7, 0);
    } else {
      // Turn on
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }
    delay(timeInterval);
    timeElapsed += timeInterval;
  }

  if (printSerial) {
    NeoSerial.println("Finished Estop test.");
  }
}

void estopHSTest(bool printSerial, int delayMs) {
  if (printSerial) {
    NeoSerial.println("Starting Estop Handshake Test.");
  }

    int timeElapsed = 0;
  const int timeInterval = 5;
  while (timeElapsed < delayMs) {
    if (digitalRead(EMERGENCY_STOP_PIN) == LOW) {
      // Active signal; return handshake
      digitalWrite(EMERGENCY_HANDSHAKE, HIGH);
    } else {
      // turn off handshake
      digitalWrite(EMERGENCY_HANDSHAKE, LOW);
    }
    delay(timeInterval);
    timeElapsed += timeInterval;
  }

  if (printSerial) {
    NeoSerial.println("Finished Estop Handshake test.");
  }
}


#endif // PCB_TEST
