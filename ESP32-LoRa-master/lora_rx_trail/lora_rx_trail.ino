

#include <SPI.h>
#include <LoRa.h>   
int LED = 3;
String inString = "";    // string to hold input
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() 
   {
  
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  { 
      
    while (LoRa.available())
    Serial.println("LoRa recv");
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString.toInt();       
    }
    inString = "";     
    LoRa.packetRssi();    
  }
      
  Serial.println(val);  
  digitalWrite(LED,LOW );
  delay (2000);
  digitalWrite(LED,LOW);
  
}
