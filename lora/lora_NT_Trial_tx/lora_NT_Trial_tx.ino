#include <SPI.h>
#include <LoRa.h> //Download here: http://electronoobs.com/eng_arduino_LoRa_SX1278.php.php
//int pot = D5;
const int buttonPin = 5; 
int val = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(buttonPin,INPUT);
  
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() 
  {
  //int val = map(analogRead(pot),0,1024,0,255);
  LoRa.beginPacket();  
  int val = digitalRead(buttonPin);
   LoRa.beginPacket();
  LoRa.print(val);
  LoRa.endPacket();
  delay(50);
   
 }
