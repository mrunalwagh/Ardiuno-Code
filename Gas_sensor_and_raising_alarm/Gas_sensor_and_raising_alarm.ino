/*  Interfacing Gas sensor and raising alarm */

int sensorPin=A0;                                        
int buzzerPin=3;
int sensorValue;                                          

void setup()
 {
    Serial.begin(9600);                                             
    pinMode(sensorPin, INPUT);     
    pinMode(buzzerPin, OUTPUT);    
}

void loop()
 {
    sensorValue=analogRead(sensorPin);   
    Serial.print("Sensor Value is:");
    Serial.println(sensorValue);                                         
    delay(1000);
      if(sensorValue>=150)                                             
      {
           digitalWrite(buzzerPin, HIGH);   
      }
      else
      {
        digitalWrite(buzzerPin, LOW);       
      }
}
