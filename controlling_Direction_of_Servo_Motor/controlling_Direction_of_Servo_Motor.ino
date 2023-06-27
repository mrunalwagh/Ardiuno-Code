//Interfacing and controlling Direction of Servo Motor
/* Sample code-1 */
/*  Interfacing and controlling direction of Servo Motor*/

#include <Servo.h>          // Arduino library file for Servo motor;
Servo myservo;              //define object for motor;

void setup() 
{
    myservo.attach(3);      //pin functionality using user object; 
} 

void loop() 
{
    myservo.write(180);       //motor will rotate and will stop at 180 degrees;
    delay (1000);                  //motor will wait at 180 degrees for 1 sec;
    myservo.write(0);                   
    delay (1000);                              
}
