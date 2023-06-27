/* Sample code (Stepper motor-Clockwise)*/
/* Interfacing & Controlling the speed of DC motor */

int dcMotor=3;

void setup() 
{
  Serial.begin(9600);                   //Set baud rate serial monitor
  pinMode(dcMotor,OUTPUT);          
}

void loop() 
{
    analogWrite(dcMotor,99);  // give output value between 0 to 255 
    delay(2000);              
  
    analogWrite(dcMotor,135); 
    delay(2000);             
 
    analogWrite(dcMotor,195); 
    delay(2000);         
 
    analogWrite(dcMotor,255); 
    delay(2000);      
 }
  
   
