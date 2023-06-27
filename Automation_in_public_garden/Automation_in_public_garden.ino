#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>     
LiquidCrystal lcd(2,3,4,5,6,7);
float time1=0,time2=0,distance=0,distance1=0;
int distanceInMm,distanceInMm1;
int range ;
String dhm;
String datavalues;
//#include "RTClib.h"
//RTC DS3231 rtc;    //rtc object creation 
#include <Wire.h>
#include <Adafruit_MLX90614.h>


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <Arduino.h>

    #define GLED 45
    #define RLED 43
    #define buzzer 32
    #define Relay 38
    #define DIR 31
    #define STEP 29
    #define SLEEP 13
    SCK=52
CS=53
MOSI=50
MISO=51
------------------------------------------
SPKR=46
BUTTON 1=44
BUTTON 2 EMG=40
BUTTON 3=38
------------------------------------------
EXT IR=39
INT IR=41
------------------------------------------
LED GREEN=21
LED RED=23
------------------------------------------
RS=7
E=6
D4=5
D5=4
D6=3
D7=2
-------------------------------------------
RELAY=8
LMP=9
18=TX=RX
19=RX=TX


void setup()
  {
    lcd.begin(16,2);
    Serial.begin(9600);
    
    pinMode(Relay,OUTPUT);
    pinMode(buzzer,OUTPUT); 
    pinMode(GLED,OUTPUT);
    pinMode(RLED,OUTPUT);


  /* if (! rtc.begin())
         {
              Serial.println("Couldn't find RTC");
               // while (1);
         }
        if (rtc.lostPower())
        {
              Serial.println("RTC lost power, let’s set the time!");
            // January 21, 2014 at 3am you would call:
            // rtc.adjust(DateTime(2016, 11, 03, 12, 22, 0));
            //  rtc.adjust(DateTime(year , month,date, 10, 56, 00));  //working format
            // rtc.adjust(DateTime(2020, 07, 28, 10, 57, 00)); 
          
         }
         //   rtc.adjust(DateTime(2020,12,25,5,59,00)); 
*/

    
    }
  void loop()
    {

    void funDateTime();

    if(f==1)
    {
      
      }
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Welcome to SNJB");
     delay(1000);
     
    //int GLED =45;
    //int RLED =43;
    //int buzzer=8;
    //int Relay=38;//==============**************need to define pin number
    //pinMode(Relay,OUTPUT);
    //pinMode(buzzer,OUTPUT); 
    //pinMode(GLED,OUTPUT);
    //pinMode(RLED,OUTPUT);
    float TEMP=mlx.readObjectTempF()+8;
     
  
    //----------------Main Program
     do {
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
        digitalWrite(RLED,LOW);
        digitalWrite(buzzer,LOW);
        Serial.println("RLED buzzer");
        
        }
        else if(distanceInMm<70)
        { 
         lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("TEMP:");
         lcd.print(TEMP);
          digitalWrite(GLED,HIGH);
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          digitalWrite(GLED,LOW);
          digitalWrite(RLED,LOW);
          digitalWrite(Relay,HIGH);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Sanitising..");
          delay(7000);
          digitalWrite(Relay,LOW);
      
  

  //------------------------------
  void funDateTime()
{

DateTime now = rtc.now();
String strDate =   String(now.day(), DEC) + '/' + String(now.month(), DEC) + '/' + String(now.year(), DEC);
String strTime=String(now.hour(), DEC) + ':' + String(now.minute(), DEC) + ':' + String(now.second(), DEC);

dhm=strDate+" "+strTime;


Serial.println("date time as follow ----------------------------------------------------------------------------------");
Serial.println(dhm);
Serial.println("..... am printing date time ");
  
   funShowOnLCD("Time",strTime,"DATE","strDate");
   
//Serial.println(strDate);
//Serial.println(strTime);
//delay(1000);

}

//--------------Show on lcd
void funShowOnLCD(String msg1,String val1,String msg2,String val2)
{

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg1);
    lcd.print(val1);
    //lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(msg2);
    lcd.print(val2);
    delay(1000);
    lcd.clear();   
}
//--------------------
