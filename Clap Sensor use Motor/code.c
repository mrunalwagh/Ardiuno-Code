/*For this project you will have to connect external power supply of 9V or 5V to the 12V pin of driver.*/
int soundSensor=2; //This is the input pin connected to digital output of sound sensor
int LED=4; //This pin is connected to led for indication and input to motor driver
int stat = 5; //This pin is used as input to verify that LED pin is on or off
void setup() {
 pinMode(soundSensor,INPUT);
 pinMode(LED,OUTPUT);
 pinMode(stat,INPUT);
}

void loop() {
 stat = digitalRead(5);
  int SensorData=digitalRead(soundSensor); 
  //Now to turn on
  if(SensorData==1) //If the sensor detected any sound
  {
     if(stat==false) //And if Led pin is false or off
     {
       
        digitalWrite(LED,HIGH);//We will turn onn the input pin for H-Bridge driver and LED
       
digitalWrite(8, LOW);//This is to ensure that our DC motor rotates in one direction
     }
    }
  
   
  //Now to turn off
   if(SensorData==1) //If the sensor detected any sound
   {

    if(stat==true) //And if Led pin is true or on
    {
     
        digitalWrite(LED,LOW); //Now the dc motor won't work as there is no input to the driver
       
    
   
    }
  
 } 
}
  