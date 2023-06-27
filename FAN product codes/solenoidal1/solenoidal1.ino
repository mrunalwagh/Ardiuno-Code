int relay_pin=1;
void setup() {
 // put your setup code here, to run once:

pinMode(relay_pin,OUTPUT);
}

void loop() {
 digitalWrite(relay_pin,HIGH);
delay(5000);  
digitalWrite(relay_pin,LOW);
delay(5000);

}
