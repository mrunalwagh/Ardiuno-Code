
int buzzerPin=8;
void setup() 
{

pinMode(buzzerPin, OUTPUT);  
}

void loop() 
{
digitalWrite(buzzerPin, HIGH);        
delay(2000);                       
digitalWrite(buzzerPin, LOW);         
delay(2000);                       
}
