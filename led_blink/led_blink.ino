int led = A0; // the pin the LED is connected to
void setup()
{
  pinMode(led, OUTPUT); // Declare the LED as an output
}

void loop()
{
 digitalWrite(led, HIGH);
 delay(2000);
  digitalWrite(led, LOW);
  delay(2000);
}
