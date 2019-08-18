// Code for Transmitter using Arduino NANO
// Writen by Madeline Younes
//Ensure CH340 driver is downloaded and Atmega328(old bootloader) is selected

//Include needed Libraries at beginning
#include <nRF24L01.h> // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include <RF24.h>
#include <SPI.h>

#define GLED_PIN 3 // GREEN LED is connected to pin 3 indicating if receiving 
#define RLED_PIN 4 // RED LED is connected to pin 4 indicating if the emergency stop is activated 
                  //either because it is not receiving or the button is pressed 
#define BLED_PIN A7 // BLUE LED indicates if the stop signal is active
#define EM_S_switch 5 // pin allocated to acting as an on off switch on the Motor Controller acting as a software emergy off
#define EM_T_switch 7 // pin  allocated to the transistor which can drive the motor signal to ground 
#define ESTOP_HANDSHAKE_PIN 6 // pin to see if handshake signal has been sent from mega

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
int switchToggle = 1;
int check = 0;

RF24 radio(10,9); // NRF24L01 used SPI pins + Pin 10, 9 (CE, CSN)

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(void){
    Serial.begin(9600);
    radio.begin(); // Start the NRF24L01
    radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening(); // Listen to see if information received
    
    pinMode(GLED_PIN, OUTPUT); // Green LED indicates that a signal is being recieved from the RF transmitter
    pinMode(RLED_PIN, OUTPUT); // Red LED indicates that a signal is not being recieved from the RF transmitter
    pinMode(EM_S_switch, OUTPUT); // motor controller output
    pinMode(EM_T_switch, OUTPUT); // Emergency transistor switch

    digitalWrite(EM_S_switch, LOW);
}

void loop(void){
    while (radio.available()){
        radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
        //Serial.print("Radio is available\n");
        
        if (ReceivedMessage[0] == 111){ // Indicates emergency stop switch is pressed
            Serial.print("Received 111\n");
            digitalWrite(GLED_PIN, HIGH); // set the  G LED on
            digitalWrite(RLED_PIN, HIGH); // set the R LED on

            if (switchToggle == 0 && check == 1) {
                digitalWrite(BLED_PIN, LOW);
                switchToggle = 1;
                check = 0;
                digitalWrite(EM_S_switch, LOW); // indicate to the motor controller that the emergy button is pressed
                delay(100); // wait one millisecond allowing for the software off to occur    
                digitalWrite(EM_T_switch, LOW); // shift transistor to ground acting as a hardware stop
            } else if (switchToggle == 1 && check == 1) {
                digitalWrite(BLED_PIN, HIGH);
                switchToggle = 0;
                check = 0;
                digitalWrite(EM_S_switch, HIGH); // indicate to the motor controller that the emergy button is pressed
                delay(100); // wait one millisecond allowing for the software off to occur    
                digitalWrite(EM_T_switch, HIGH); // shift transistor to ground acting as a hardware stop
            }
            
        } else if (ReceivedMessage[0] == 000) {
            // When the transmitter is not connected
            Serial.print("Received 000\n");
            digitalWrite(GLED_PIN, LOW); // set the G LED off
            digitalWrite(RLED_PIN, HIGH); // set the R LED on
            digitalWrite(EM_T_switch, HIGH); // shift transistor to ground acting as a hardware stop
        } else {
            Serial.print("Recieved else\n");
            digitalWrite(GLED_PIN, HIGH); // set the  G LED on
            digitalWrite(RLED_PIN, LOW); // set the R LED off
            check = 1;
        }
    }
    if (radio.available() == 0) {
      Serial.print("fail\n");
      digitalWrite(GLED_PIN, LOW); // turn off G LED to indicate not receiving
      //delay(500);
    }
}
