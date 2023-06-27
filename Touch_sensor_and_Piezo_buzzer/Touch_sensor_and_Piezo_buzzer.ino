/*   Interfacing touch sensor and Piezo buzzzer  */
int touchSensorPin = 2;
int buzzerPin = 12;  
int sensorValue;

void setup() 
{
  Serial.begin(9600);                
  pinMode(touchSensorPin, INPUT);       
  pinMode(buzzerPin, OUTPUT);        
}

void loop() 
{
  sensorValue = digitalRead(touchSensorPin)
  Serial.print("Touchsensor value is:");
  Serial.println(sensorValue);      
  if(sensorValue==HIGH)            
  {
    digitalWrite(buzzerPin, HIGH);   
    Serial.println("Buzzer is on");           
    delay(2000);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
    Serial.println("Buzzer is off");
    delay(1000);  
  }
}
