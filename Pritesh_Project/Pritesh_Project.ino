//------------------------------------------------------------------------------------------------------------------Disp+Ultra
#include <LiquidCrystal.h>//Display
//------------ultra 1
#define trigger 11
#define echo 10
//-----------ultra 2
#define trigger1 37
#define echo1 35
int f=1;//flag for initial motor
LiquidCrystal lcd(2,3,4,5,6,7);
float time1=0,time2=0,distance=0,distance1=0;
int distanceInMm,distanceInMm1;

//------------------------------------------------------------------------------------------------------------------Disp+Ultra End
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//------------------------------------------------------------------------------------------------------------------Temp Data End
#include "BasicStepperDriver.h"//---------------------------------------------------------------------------------steper motor
#include <Arduino.h>
//----------------
    #define GLED 45
    #define RLED 43
    #define buzzer 8
    #define Relay 38
//-----------------
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 30

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 31
#define STEP 29
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
//---------------------------------------------------------------------------------------------------------------------

void setup()
  {
    lcd.begin(16,2);
    stepper.begin(RPM, MICROSTEPS);
    mlx.begin();//--temp
    Serial.begin(9600);
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(trigger1,OUTPUT);
    pinMode(echo1,INPUT);
    //---------------------
    pinMode(Relay,OUTPUT);
    pinMode(buzzer,OUTPUT); 
    pinMode(GLED,OUTPUT);
    pinMode(RLED,OUTPUT);
  }
void loop()
  {
    //------------------------------------------------------------------------------------------------------------------  

    if(f==1)
    {
      stepper.rotate(90);
      f=0;
      }
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Welcome to SNJB");
     delay(1000);
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
//--
    digitalWrite(trigger1,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger1,LOW);
    delayMicroseconds(2);
    //time1=pulseIn(echo,HIGH);    
    time1=pulseIn(echo,HIGH);
    distance=(time1*340/20000);
    distanceInMm=distance*10;
    //------------------
    //time2=pulseIn(echo1,HIGH);
    time2=pulseIn(echo1,HIGH);
    distance1=(time2*340/20000);
    distanceInMm1=distance*10;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("DIST. MM");
    lcd.print(distance);
    lcd.clear();
    lcd.setCursor(0,1);
    //int GLED =45;
    //int RLED =43;
    //int buzzer=8;
    //int Relay=38;//==============**************need to define pin number
  //  pinMode(Relay,OUTPUT);
   // pinMode(buzzer,OUTPUT); 
    //pinMode(GLED,OUTPUT);
    //pinMode(RLED,OUTPUT);
    float TEMP=mlx.readObjectTempF()+8;
   
    
    /*digitalWrite(Relay,HIGH);
    delay(20000);
    digitalWrite(Relay,LOW);
    delay(20000);
    digitalWrite(Relay,HIGH);
    */
    //----------------------------------------------------------------------------------------------------------------------
    
    //----------------Main Program
     do {
      digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    time1=pulseIn(echo,HIGH);
    distance=(time1*340/20000);
    distanceInMm=distance*10;
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Put Your Hand");
     //lcd.print(distanceInMm);
     Serial.println(distanceInMm);
     Serial.println("Put");
         } while( distanceInMm>70);
    if(distanceInMm<70)
    {
     Serial.print("*Temp = "); /*Serial.print(mlx.readObjectTempF());*/Serial.print(TEMP); Serial.println("*F");
     lcd.clear();
     lcd.setCursor(0,1);
     //lcd.print("DIST:");
     //lcd.print(distanceInMm);
     lcd.print("TEMP:");
     lcd.print(TEMP);
     delay(2000);
      if(TEMP>98)
       {
        digitalWrite(RLED,HIGH);
        digitalWrite(buzzer,HIGH);
        Serial.println("High Temp");
        lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("High Temp");
        delay(5000);
        //d
       digitalWrite(RLED,LOW);
        digitalWrite(buzzer,LOW);
        Serial.println("RLED buzzer");
        
        }
        else if(distanceInMm<70)
        { 
           lcd.clear();
           lcd.setCursor(0,1);
          // lcd.print("DIST:");
           //lcd.print(distanceInMm);
           lcd.print("TEMP:");
           lcd.print(TEMP);
          digitalWrite(GLED,HIGH);
          digitalWrite(buzzer,HIGH);
           //lcd.clear();
           //lcd.setCursor(0,1);
           //lcd.print("Green LED");
          delay(500);
         // digitalWrite(GLED,LOW);
          digitalWrite(buzzer,LOW);
          
         }
       delay(1000);//---------------(orignal 7000)----------------------------------------time to hand sanitization manually
       digitalWrite(GLED,LOW);
       digitalWrite(RLED,LOW);
       digitalWrite(Relay,HIGH);
        lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("Sanitising..");
       delay(500);//------------------(orignal 3500)----------------------------------------sanitization time
       digitalWrite(Relay,LOW);
       //-------------------------steper motor
      if (TEMP<98)
      {
        // energize coils - the motor will hold position
        // stepper.enable();
      
        /*
         * Moving motor one full revolution using the degree notation
         */
         
        /*stepper.rotate(180);
         lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("Stepper");
            delay(5000);
        stepper.rotate(-180);*/
        /*
         * Moving motor to original position using steps
         */lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("Barrier Open");
            delay(1000);
        stepper.rotate(340);
        do{
          lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("Thanks ");
         digitalWrite(trigger1,LOW);
        delayMicroseconds(2);
        digitalWrite(trigger1,HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger1,LOW);
        delayMicroseconds(2);
        time2=pulseIn(echo1,HIGH);
        distance1=(time2*340/20000);
        distanceInMm1=distance1*10;
         lcd.print(distanceInMm1);
       
         Serial.println(distanceInMm1);
         
            delay(1000);
          
          }while(distanceInMm1>8700);
          delay(3000);
        
        stepper.rotate(-340);
    
        // pause and allow the motor to be moved by hand
        // stepper.disable();
         lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("Thank You!!");
         delay(1000);
        
     
      }
      
      
      } 
    
    
  /*  lcd.print("DIST. MM");
    lcd.print(distanceInMm);
    
    
    Serial.println(round(distance));
    Serial.println(round(distanceInMm));*/
    lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("......");
            delay(1000);
   
  }
