const int lamp = 13;


void setup() {
  Serial.begin(9600);
  pinMode(lamp , OUTPUT);

}

void loop() {
  int c = analogRead(A1);
  delay(500);
  Serial.println(c);
  
if ( c<450 ){
  digitalWrite(13,HIGH);
   delay(1000);

}
else if ( c >450){
digitalWrite(13,LOW);
delay(1000);
}
}
