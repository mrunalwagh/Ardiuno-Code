#include<Servo.h>
Servo Myservo;
int pos;
void setup()
{
Myservo.attach(D4);
}

void loop()
{
  
  
for(pos=0;pos<=120;pos++){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
  for(pos=120;pos>=0;pos--){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
}
