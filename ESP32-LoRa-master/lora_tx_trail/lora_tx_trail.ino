
#include <SPI.h>
#include <LoRa.h> //Download here: http://electronoobs.com/eng_arduino_LoRa_SX1278.php.php
int pot = 8;
int pinButton = 3;
int LED = 13;
int stateLED = LOW;
int stateButton;
int previous = LOW;
long time = 0;
long debounce = 200;

void setup() {
  Serial.begin(9600);
  pinMode(pinButton,INPUT_PULLUP);
  
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
 // int val = 1;
  stateButton = digitalRead(pinButton);  
  if(stateButton == HIGH && previous == LOW && millis() - time > debounce) {
    if(stateLED == HIGH){
      stateLED = LOW; 
    } else {
       stateLED = HIGH; 
    }
    time = millis();
  
  digitalWrite(LED, stateLED);
  previous == stateButton;
  LoRa.beginPacket();
  Serial.println("LoRa Send");  
  LoRa.print(stateButton);
  LoRa.endPacket();
  delay(50);
  }
}
