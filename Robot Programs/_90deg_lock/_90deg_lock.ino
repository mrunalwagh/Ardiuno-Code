#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() 
{ 
  servo1.attach(4);
  servo2.attach(7);
  servo3.attach(9);
  servo4.attach(11);
} 

void loop() 
{ 
    servo1.write(90);              
    servo2.write(90);              
    servo3.write(90);              
    servo4.write(90);              
    delay(15);                       
} 
