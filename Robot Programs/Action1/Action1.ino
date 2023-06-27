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

  servo1.write(90);              
  servo2.write(90);              
  servo3.write(90);              
  servo4.write(90);
  delay(2000);  //Stay in Lock Position for 2 Sec
} 

void loop() 
{ 
  for(pos = 90; pos > 70; pos--)  
  {                                  
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(90);              
    servo4.write(90);              
    delay(15);                       
  } 
  for(pos = 70; pos<=90; pos++)     
  {                                
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(90);              
    servo4.write(90);              
    delay(15);                       
  } 
  for(pos = 90; pos < 110; pos++)  
  {                                  
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(90);              
    servo4.write(90);              
    delay(15);                       
  } 
  for(pos = 110; pos>=90; pos--)     
  {                                
    servo1.write(pos);              
    servo2.write(pos);              
    servo3.write(90);              
    servo4.write(90);              
    delay(15);                       
  } 
} 
