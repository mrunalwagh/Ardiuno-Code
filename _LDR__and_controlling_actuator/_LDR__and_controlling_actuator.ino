/* Interfacing LDR and lighting LED of Arduino board */

int sensorValue;
int lampPin = 13;
int ldrPin = A0;
int threshold = 450;       // set threshold

void setup()
{
  pinMode(ldrPin, INPUT);                  
  pinMode(lampPin, OUTPUT);          
}

void loop()
{
  sensorValue = analogRead(ldrPin);
  serial.print(“Sensorvalue is:  “);
  seial.println(sensorValue);

  if (sensorValue > threshold)
  {
    digitalWrite(lampPin, HIGH);
  }
  else
  {
    digitalWrite(lampPin, LOW);
  }
}
