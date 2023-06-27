void setup(void)
{

  Serial.begin(9600);
  
}

void loop(void)
{
  int i=98;
  char ch=98;
  Serial.println("am printing char");
  Serial.println(ch);
  delay(1000);
}
