#include <stdlib.h>

char serial;
int RELAY1=13;                      
void setup()
{    
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);       
}

void loop()
{
  if(Serial.available() > 0)
  {
      serial = Serial.read();
      Serial.println( serial, HEX);
      if (serial=='s')
      {
        digitalWrite(RELAY1,HIGH);           
        Serial.println("Light ON");
        delay(2000);                                      
        digitalWrite(RELAY1,LOW);          
        Serial.println("Light OFF");
        delay(2000);
      }
   } 
}
