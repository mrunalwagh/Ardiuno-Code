 #include <Servo.h> // Library for Servo
Servo myservo; // Name of my Servo
int led = 13;

int sensor = 7; // Sensor is connected to D2
int state = LOW; // Initial value for variable state is low
int val = 0; // Initial value for variable val is 0
void setup() {
pinMode(led, OUTPUT);
myservo.attach(8); // Servo is connected to D9
pinMode(sensor, INPUT); // D2 is set as a Input
Serial.begin(9600); // Start for Serial Communication
}
void loop() {
val = digitalRead(sensor);
if(val==HIGH){
digitalWrite(led, HIGH);
myservo.write(60);
if (state == LOW){
Serial.println("Motion Detected");
state = HIGH;
}

}
else {
digitalWrite(led, LOW);
myservo.write(180);
if(state == HIGH){
Serial.println("Motion Stopped");
state = LOW;
delay(5);
}
}
}
