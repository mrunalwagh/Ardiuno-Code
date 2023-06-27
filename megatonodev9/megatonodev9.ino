
#include<LiquidCrystal.h>    //display 1
#include <RTClib.h>
#include <SoftwareSerial.h>
//SoftwareSerial mySerial(52,53);
SoftwareSerial mySerial(53,52); //tx,rx
SoftwareSerial mton(10,11);
const int sensorMin = 0; 
const int sensorMax = 1024; 
#include <SPI.h> 
int range;
//--------------
RTC_DS3231 rtc;
#include "DHT.h"

#define DHTPIN 41
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
const int soilPinAnalog = A5;  /* Soil moisture sensor O/P pin */// initialize sensor pin
const int soilPinDigital = 40;  /* Soil moisture sensor O/P pin */// initialize sensor pin
String datavalues;

float t, h;

//------------
float moisture_percentage;
  int sensor_analog;

//----------------

/*  original
int en=3;  //  display 3
int rs=4;  //  display 2
int d4=5;  //  display 4
int d5=6;  //  display 5
int d6=7;  //  display 6
int d7=8;  //  display 7

/*
int en=3;  //  display 3
int rs=4;  //  display 2
int d4=8;  //  display 4
int d5=7;  //  display 5
int d6=6;  //  display 6
int d7=5;  //  display 7
*/

LiquidCrystal lcd(3,4,5,6,7,8);
//LiquidCrystal lcd(8,7,6,5,3,4);
//LiquidCrystal lcd(8,7,6,5,4,3);
//LiquidCrystal lcd(rs,en,d4,d5,d6,d7);   //display 7// configure the pin RS,enable,D4,D5,D6,D7  resp.  //original
int buzzerPin = 40;  
int pinPowerLED=43;

 String strdd="";
   String strmonth="";
   String stryy="";
   String  dhm ="";
   String strmm="";
   String strss="";
   String strhh="";
//----------------
void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  mton.begin(9600);
pinMode(soilPinAnalog, INPUT); 
pinMode(soilPinDigital, INPUT); 
pinMode(pinPowerLED,OUTPUT);
pinMode(DHTPIN, INPUT); 


dht.begin();



//------------rtc
if (! rtc.begin())
  {
     Serial.println(" in rtc begin ");
    Serial.println(" Couldn't find RTC ");
    while (1);
  }
    else
   {
      Serial.println("RTC Module is ok..."); 
   }
  if (rtc.lostPower())
  {Serial.println(" in lost power ");
    Serial.println(" RTC lost power, let’s set the time! ");
    // January 21, 2014 at 3am you would call:
   // rtc.adjust(DateTime(2018, 20, 03, 02, 01, 00));
   // rtc.adjust(DateTime(2018, 1,16 , 5, 8, 30)); //set current time and cut paiste same line outside of for loop
  }
  // rtc.adjust(DateTime(2020,9,7, 18,53, 00));   // to renter time *************************************************************
 Serial.println(" ibelow date adjusted ");

//-------------
//-------------------------------------------------------------------------------------------------------------------------------------
    lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9

    //clear the screen
    lcd.print("   Welcome   ");  //displaying the message on LCD
    delay(1000);
    
     lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9
     mySerial.begin(9600);
    //clear the screen
    lcd.print("  Grapes IoT V10");  //displaying the message on LCD
    Serial.println("Grapes IoT V10");
    delay(1000);
  
}

//-------------------------------------------------------------------------------------------------

void loop() {

testCountDown(20000/1000);
//SendMessage();
//SendMessageDisease(10.10,"cloudy","powerdery");
 
 /*
 lcd.clear();
 lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
 lcd.print("one");

  lcd.setCursor(1,1);       // set the cursor at position (C1,R0)  //display 8
   lcd.print("two");
  delay(2000);

  */
Serial.println("\n\n");
digitalWrite(pinPowerLED,HIGH);
   delay(100);
   digitalWrite(pinPowerLED,LOW);\
   delay(800);
   // delay(dht.getMinimumSamplingPeriod());

   h  = dht.readHumidity();
  t= dht.readTemperature();
  DateTime now = rtc.now();


Serial.print("\n This is time of RTC ");
strdd=String(now.day());
strmonth=String(now.month());
stryy=String( now.year());
strhh =  String(now.hour());
strmm =  String( now.minute());
strss =  String( now.second());
 
dhm=strdd+":"+strmonth+":"+stryy+" "+strhh+":"+strmm+":"+strss;

showOnLCD("Time Stamp",dhm);
Serial.println("Time is ");
Serial.println(dhm);
   if (isnan(h) || isnan(t) ) {    //|| isnan(f)
    Serial.println(F("Failed to read from DHT sensor!"));
   }    

     
      Serial.print("Temperature=");
      Serial.println(t,1);                                  
    //  Serial.print("Humidity=");
     // Serial.println(h,1);      

      range=chkRainLevel();
      Serial.println("Range:");
        Serial.println(range);



                                
 
   
    
    delay(2000);

  if(range==0 &&  t>=18 && t<=25)  //0 rainy(heavy(,1 warning(cloudy) ,2 not raining 
  {

    //print on lcd
 
    showOnLCD3(t,"Heavy Rain","Downey");
    SendMessageDisease(t,"Heavy Rain","Downey");  //void SendMessage(float temp,String strRainCondion,String Dis)
    showOnLCDGeneral("Text Msg","sent");
    
    Serial.print("Message Heavy Rain Downey done");
    delay(1000);
  }
  else if(range==1 && t>=22 && t<=30 ) //  0 1 2   //$ change to 30max limit
  {

    //print on lcd
   
     showOnLCD3(t,"Cloudy","Powdery");
    SendMessageDisease(t,"Cloudy and Rain Warn","Powdery");  // void SendMessage(float temp,String strRainCondion,String Dis)
    showOnLCDGeneral("Text Msg","sent");
   Serial.print("Message Cloudy Powdery send done");
   delay(1000);
   
  }
  
  else if(range==0)
{
  Serial.println("only heavy rain");
  Serial.println("Temperature is:");
  Serial.println(t);
  showOnLCD("Only Heavy Rain",String(t));
  delay(1000);
}
  else if(range==1)
  {
     Serial.println("Cloudy enviroment,Rain Warning");
     Serial.println("Temperature is:");
     showOnLCD("Cloudy & Rn Warn",String(t));
     Serial.println(t);
     delay(1000);
  }
  else
  {
     showOnLCD("No Rain",String(t));
    // showOnLCD(Disease","Powdery") ;//title,msg
     //SendMessageDisease();
    Serial.print("No Rain");
  Serial.println("Temperature is:");
  Serial.println(t);
   delay(1000);
   // showOnLCD("No","Rain")


  }
  



   //send h an range to node mcu

   

      showOnLCDGeneral("data sending to","cloud....");
     sendValues(t,range,dhm);  //void sendValues(int float temp1,int range1)
     showOnLCDGeneral("data sending to","cloud done");
     showOnLCDGeneral("Wait..."," ");

}


//-----------------------------gsm code


void showOnLCD(String title,String msg)
{
     lcd.clear();       ////display 9
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print(title);  //displaying the message on LCD
        lcd.setCursor(0,1); 
       
       lcd.print(" Temp:");  //displaying the message on LCD
     lcd.print(msg);  //displaying the message on LCD
     delay(2000);
}
void showOnLCDGeneral(String title,String msg)
{
     lcd.clear();       ////display 9
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print(title);  //displaying the message on LCD
        lcd.setCursor(0,1); 
         
     lcd.print(msg);  //displaying the message on LCD
     delay(2000);
}
void showOnLCD3(float temp,String strRainCondion,String Dis)
{
     lcd.clear();       ////display 9
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
     lcd.print(temp);  //displaying the message on LCD
     lcd.print(" "); // Space
      lcd.print(strRainCondion);  //displaying the message on LCD
      lcd.print(" ");  //Space
      lcd.setCursor(0,1); 
      lcd.print(Dis);  //displaying the message on LCD
     delay(2000);
}
int chkRainLevel()
{

int sensorReading = analogRead(A14);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

   return(range);
  delay(1000); 

}

//------------------------


void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  mySerial.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
  String Str="Temp 30.30  Rain Condition: Cloudy Disease :Powedery";
  mySerial.println( Str);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void SendMessageDisease(float temp,String strRainCondion,String Dis)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  mySerial.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number   anant 
 // mySerial.println("AT+CMGS=\"+918668746346\"\r"); // Replace x with mobile number    Sanghavi Sir
  // mySerial.println("AT+CMGS=\"+919921343342\"\r"); // Replace x with mobile number    Sanghavi Mam
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
 // mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  String  tempStr=String(temp);
  String str="Temp:"+tempStr+" "+"Rain Condition:"+strRainCondion; //+" "+"Disease:"+Dis;
   mySerial.println(str);// The SMS text you want to send
   delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


//--------------------------------------------------------



void sendValues(float temp1,int range1,String dhm1)
{
   
Serial.println("\nvalues before uploading to gateway");
Serial.println("\nTempraturevalue is:");
Serial.println(temp1);
Serial.println("\n Range value is:");
Serial.println(range1);
Serial.println("\n Time Stamp is");
Serial.println(dhm1);
Serial.println("\n Now sending");

//datavalues =String(String(temp1)+String(",")+String(range1)+String(","));
datavalues =String(String(temp1)+String(",")+String(range1)+String(",")+String(dhm1)+String(","));
//splitStr(datavalues);

Serial.println("Print data Values array ");
Serial.println(datavalues);
mton.println(datavalues);
Serial.println("Data sent to node mcu  sucessfully");


}

//--------------------------------------------------------


void testCountDown(int sCount) {

  for(;sCount>0;sCount--)
  {
  
     lcd.clear();       ////display 9
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print("Wait : ");  //displaying the message on LCD
     lcd.print(sCount);  //displaying the message on LCD
     
     delay(1000);
 
  }
}

