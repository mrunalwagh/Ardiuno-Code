//Interfacing IR sensor and detecting object (Proximity)
/* Sample code-1 */
/* Interfacing IR sensor (Proximity Sensor) with Arduino board and detecting object */
int ledPin = 13;
int sensorPin = 7;
int sensorValue;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
void loop()
{
  delay(1000);
  sensorValue = digitalRead(sensorPin);
  Serial.print("Sensor Value is :");
  Serial.println(sensorValue);

if (sensorValue == HIGH)    //not detected
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Object is not detected");
  }
if (sensorValue == LOW)   //detected
  {
    digitalWrite(ledPin, LOW);
    Serial.println("Object is detected");
  }
}

