#include <dht11.h>
#define DHT11PIN 2

dht11 DHT11;
const int lamp = 13;
int Fan = 8 ;

void setup()
{
  Serial.begin(9600);
  pinMode(lamp , OUTPUT);
  pinMode(Fan , OUTPUT);
 
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);


  if(DHT11.temperature>34)
  {          
    digitalWrite(Fan,HIGH);   
    delay(1000);
   
    
  }
  else 
  {
      digitalWrite(Fan ,LOW);
      delay(1000);
  }

  //delay(2000);

  
  int c = analogRead(A1);  
  Serial.println(c);
  if ( c < 450 )
  {
  digitalWrite(13,HIGH);
  delay(1000);
  }
  else if ( c > 450)
  {
  digitalWrite(13,LOW);
  delay(1000);
  }
  
  
}

  
