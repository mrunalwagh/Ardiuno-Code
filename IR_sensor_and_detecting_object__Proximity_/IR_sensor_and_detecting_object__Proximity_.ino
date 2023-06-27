/* Interfacing IR sensor (Proximity Sensor) with Arduino board and detecting object */
int ledPin = 13;
int sensorPin = 2;
int sensorValue;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
void loop()
{
  sensorValue = digitalRead(sensorPin);
  Serial.print("Sensor Value is :");
  Serial.println(sensorValue);

  if (sensorValue == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Object is detected");
  }
  if (sensorValue == LOW)
  {
    digitalWrite(ledPin, LOW);
    Serial.println("Object is not detected");
  }
}
