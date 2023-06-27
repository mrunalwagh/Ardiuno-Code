#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pos = 0;

void setup() 
{ 
  servo1.attach(4);
  servo2.attach(7);
  servo3.attach(9);
  servo4.attach(11);
} 

void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  
  {                                  
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(pos);              
    servo4.write(pos);              
    delay(15);                       
  } 
  for(pos = 180; pos>=1; pos-=1)     
  {                                
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(pos);              
    servo4.write(pos);              
    delay(15);                       
  } 
} 
