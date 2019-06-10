// Encoder variables
#define encoderPinA 2
#define encoderPinB 3
#define encoderPinC 4
#define readA bitRead(PIND,2)
#define readB bitRead(PIND,3)
#define readC bitRead(PIND,4)

volatile long encoderCounts = 0;
unsigned long start;
const int cpr = 200;
int rps = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(encoderPinB, INPUT_PULLUP);      // sets pin B as input
  pinMode(encoderPinC, INPUT_PULLUP);      // sets pin C as input

  // Attach pins to encoder interrupt function
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}

void loop() {
  // Update rpm every second
  if(millis() - start > 1000) {
    start = millis();
    noInterrupts();
    rps = encoderCounts/cpr;
    encoderCounts = 0;
    interrupts();
  }
}

void isrA() {
  if(readC) return;
  readA != readB ? encoderCounts++:encoderCounts--;
}

void isrB() {
  if(readC) return;
  readA == readB ? encoderCounts++:encoderCounts--;  
}
