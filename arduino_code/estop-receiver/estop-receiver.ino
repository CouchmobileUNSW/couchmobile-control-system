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
#define EM_H_switch 7 // pin  allocated to the transistor which can drive the motor signal to ground 
#define ESTOP_HANDSHAKE_PIN 6 // pin to see if handshake signal has been sent from mega

// ===== Settings =====
#define HARDWARE_STOP // If set to true: will turn off motor control by overriding the control signal if a handshake is not received
                      // If set to false: will always pass through control signal.

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
int switchToggle = 1;
int check = 0;

RF24 radio(10,9); // NRF24L01 used SPI pins + Pin 10, 9 (CE, CSN)

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void switchHardEstop(bool toggleOn);
void switchSoftEstop(bool toggleOn);

void setup(void){
    Serial.begin(9600);
    radio.begin(); // Start the NRF24L01
    radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening(); // Listen to see if information received
    
    pinMode(GLED_PIN, OUTPUT); // Green LED indicates that a signal is being recieved from the RF transmitter
    pinMode(RLED_PIN, OUTPUT); // Red LED indicates that a signal is not being recieved from the RF transmitter
    pinMode(EM_S_switch, OUTPUT); // motor controller output
    pinMode(EM_H_switch, OUTPUT); // Emergency transistor switch

    // Begin with E-stop on
    switchSoftEstop(true);
    switchHardEstop(true);
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
                // Turn on the motors
                digitalWrite(BLED_PIN, LOW);
                switchToggle = 1;
                check = 0;
                switchSoftEstop(false);
                delay(100);
                #ifdef HARDWARE_STOP
                    // Check if handshake signal received
                    if (digitalRead(ESTOP_HANDSHAKE_PIN) == LOW) {
                        // All is good. Turn on motors
                        switchHardEstop(false);
                    } else {
                        // Turn off motor control manually
                        switchHardEstop(true);
                    }
                #endif
            } else if (switchToggle == 1 && check == 1) {
                // Turn off the motors
                digitalWrite(BLED_PIN, HIGH);
                switchToggle = 0;
                check = 0;
                switchSoftEstop(true);   
                #ifdef HARDWARE_STOP
                    // Wait some time for handshake signal to activate
                    delay(100);
                    // Check if handshake signal is received
                    if (digitalRead(ESTOP_HANDSHAKE_PIN) == HIGH) {
                        // All is good. Controller has turned off motors
                    } else {
                        // Turn off motor control manually
                        switchHardEstop(true);
                    }
                #endif
            }
            
        } else if (ReceivedMessage[0] == 000) {
            // When the transmitter is not connected
            Serial.print("Received 000\n");
            digitalWrite(GLED_PIN, LOW); // set the G LED off
            digitalWrite(RLED_PIN, HIGH); // set the R LED on
            switchHardEstop(true);
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

/*
 * Function written by: William Chen
 * Date: 19/08/2019
 * Description: Abstracted function to handle switching of hardware E-stop.
 *              Hardware e-stop is activated when the control board does not respond to the software e-stop.
 *              Control board response is checked through the handshake pin.
 */
void switchHardEstop(bool toggleOn) {
    // Active LOW E-stop. The motor driver signal is the output of EM_H_switch && PwmSignal
    if (toggleOn) {
        digitalWrite(EM_H_switch, LOW);
    } else {
        digitalWrite(EM_H_switch, HIGH);
    }
}

/*
 * Function written by: William Chen
 * Date: 19/08/2019
 * Description: Abstracted function to handle switching of software E-stop
 *              After this function is called, wait a few milliseconds (50ms good) and check for handshake.
 */
void switchSoftEstop(bool toggleOn) {
    // Active LOW E-stop. The motor driver signal is the output of EM_H_switch && PwmSignal
    if (toggleOn) {
        digitalWrite(EM_S_switch, LOW);
    } else {
        digitalWrite(EM_S_switch, HIGH);
    }
}
