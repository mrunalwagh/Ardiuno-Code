void setup()
int buzzer= A0;

void loop() {
  analogWrite(BUZZER, 255);
  delay(100);
  analogWrite(BUZZER, 0);
}
