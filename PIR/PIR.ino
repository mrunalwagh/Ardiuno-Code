intsensorPin=3;
intsensorValue;                              

void setup() 
{
Serial.begin(9600);                          
pinMode(sensorPin, INPUT);         
}

void loop() 
{
sensorValue= digitalRead(sensorPin);            
if(sensorValue==HIGH)
     {                                              
Serial.println("Motion is detected");
Serial.print("Sensorvalue is:");                         
Serial.println(sensorValue);
delay(500); 
     }
else
     {                               
Serial.println("Motion is not detected");
Serial.print("Sensorvalue is:");                         
Serial.println(sensorValue);
delay(500); 
     }
}
