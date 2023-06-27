#include <SPI.h>
#include <LoRa.h> //Download here: http://electronoobs.com/eng_arduino_LoRa_SX1278.php.php
#define loraTX1 4
#define loraTX2 5

void setup() {
  Serial.begin(9600);
  pinMode(loraTX1,INPUT);
  pinMode(loraTX2,INPUT);
  
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int val = digitalRead(loraTX1);
  int val1 = digitalRead(loraTX2);
  if(val == 1)
      loraTX(1);
  else()
      loraTX(2);
  if(val1 == 1)
    loraTX(3);
  else()
    loraTX(4);
 }

 void loraTX(int a)
 {
    LoRa.beginPacket();  
    LoRa.print(a);
    LoRa.endPacket();
    delay(50);
 }
