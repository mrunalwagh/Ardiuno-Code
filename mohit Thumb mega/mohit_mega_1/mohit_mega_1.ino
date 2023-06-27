#include <Adafruit_Fingerprint.h>   //thum1 
#include "DHT.h"
#include<LiquidCrystal.h>    //display 1
#include <RTClib.h>
#include <SoftwareSerial.h>
//SoftwareSerial mySerial(52,53);
SoftwareSerial mySerial(52,53); //tx,rx  ---------->thumb
SoftwareSerial mton(10,11);
#define DHTPIN 41
#define DHTTYPE DHT11   // DHT 11
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const int sensorMin = 0; 
const int sensorMax = 1024; 
#include <SPI.h> 
int range;
int sensorValueldr;
//--------------
RTC_DS3231 rtc;

int readnumber(void);
void funWelcomeToGoCart();
void SendMessageOfRegistration();
void testldr();
void testPIR();
//DHT dht(DHTPIN, DHTTYPE);
int count;
const int soilPinAnalog = A5;  /* Soil moisture sensor O/P pin */// initialize sensor pin
const int soilPinDigital = 40;  /* Soil moisture sensor O/P pin */// initialize sensor pin
String datavalues;
int pinLatch;
float t, h;
int rollNo;
uint8_t id;
int lampPin = 13;
int ldrPin = A0;
//int lampPin = 8;
int PIRPin=9;


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


//dht.begin();
//---------------
pinMode(ldrPin, INPUT); 
pinMode(PIRPin, INPUT); 
pinMode(lampPin, OUTPUT); 



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

//------------- thumb setup

 // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("\n fingerprint sensor Found Sucessfully.You can Proceed!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
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

      rollNo=takeAttendance();
  /*   
//-----------------------------------------------------temp
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

showOnLCDGeneral("Time Stamp",dhm);
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
  

//--------------------------------------------------------------------end of temp
*/
   //send h an range to node mcu

   

      showOnLCDGeneral("data sending to","cloud....");
     
     
    // sendValues(t,range,dhm);  //void sendValues(int float temp1,int range1)
     sendValues(rollNo,dhm);  //void sendValues(int float temp1,int range1)
     
     showOnLCDGeneral("data sending to","cloud done");
     showOnLCDGeneral("Wait..."," ");

testldr();
testPIR();


}  //end of loop

//----------------------takeAttendace()



int  takeAttendance()
{

  
loop_verification();
  
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



void sendValues(int rollNo1,String dhm1)
{
   
Serial.println("\nvalues before uploading to gateway");

Serial.println("\n RollNo value is:");
Serial.println(rollNo1);
Serial.println("\n Time Stamp is");
Serial.println(dhm1);
Serial.println("\n Now sending");

datavalues =String(String(rollNo1)+String(",")+String(dhm1)+String(","));
//datavalues =String(String(temp1)+String(",")+String(rollNo1)+String(",")+String(dhm1)+String(","));
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


//------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------thumb 5
void loop_registration()
{


  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  
  while (!  getFingerprintEnroll() );
  //------------------------loop registration for keypad
  /*
  char key;
 // Serial.println("Ready to enroll a fingerprint!");
  Serial.println("\n Enter ID (from 2 to 255) to be assign: \n");
  
  key=keypad.getKey();
  while(!key)
  {
    Serial.println("\n Enter Key :");
    key=keypad.getKey();
    delay(1000);
  }
  
  Serial.println("\nAm printing key value");
  Serial.println(key);
  delay(2000);
  id=(int)key-48;
  Serial.println("\nAm printing key value in int");
  Serial.println(id);
  //id = readnumber();
  if (id == 0) { // ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  
  while (!getFingerprintEnroll() );
*/
}
//----

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
//-------------------------------------------

void loop_verification()
{
     
      //Serial.println("\n am enter in loop verification \n");
     delay(2000);
     finger.getTemplateCount();
     Serial.print("System Contain "); Serial.print(finger.templateCount); Serial.println(" IDs");
     Serial.println("Waiting for valid finger...");
     getFingerprintIDez(); //don't ned to run this at full speed.
     delay(50);     
}  //loop verification

int getFingerprintIDez() {   //-------------------------------------work
  //Serial.println("\n am enter in getFingerPrintIDez");
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

     // found a match!
  Serial.print("USER ID:"); Serial.print(finger.fingerID);
  Serial.println("\n Login Successfully....");
  //---
  lcd.clear();               //clear the screen
  lcd.print("Login Sucessfull");  //displaying the message on LCD
  delay(2000);
  funWelcomeToGoCart();
  //-----
  
  
  Serial.print("USER ID:"); Serial.print(finger.fingerID); 
  Serial.print("\nMatched With Confidance level: "); Serial.println(finger.confidence);
   
  //Serial.println("\n Relay pin 13 set to high ");  
  digitalWrite(pinLatch, HIGH); 
  if(finger.fingerID==1)
  {
      Serial.println("\n Welcome Admin !!!");
      Serial.println("\n You can Register New user."); 
      SendMessageOfRegistration();

      loop_registration();
  }
  else
  {
    Serial.println("\n driver part");
  fingerID=finger.fingerID; 
  delay(3000);
  switch(fingerID)
  {
    
    case 2:
        //---------

       
        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Prashant");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD

        //----------
       Serial.println("\n Debug :am in case 2");
       Serial.println("\n Debug :calling to funPassMessage");
       Serial.println("Mr.Bagmar Prashant sir(Admin) is Driving Go-Kart");
       funPassMessage("Mr.Bagmar Prashant sir(Admin) is Driving Go-Kart ");
            break;

    case 3:
        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Sameer");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
    
       funPassMessage("Mr.Sameer Patil  is Driving Go-Kart ");
        break;
      
    case 4:
    lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Tushar");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
      funPassMessage("Mr.Kumbharde Tushar  is Driving Go-Kart ");
      break;

    case 5:
        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Akash");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
       funPassMessage("Mr.Akash Bidkar  is Driving Go-Kart ");
       break;
    case 6:

          lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Prabodh");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
          funPassMessage("Mr.Prabodh Wagh  is Driving Go-Kart ");
          break;
    case 7:

        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Aayush");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
        funPassMessage("Mr.Aayush Jain  is Driving Go-Kart ");
        break;

    case 8:

        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Sameer");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
        funPassMessage("Mr.Sameer Patil  is Driving Go-Kart ");
        break;
    case 9:

        lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Abhijit");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
        funPassMessage("Mr.Abhijit Kale  is Driving Go-Kart ");
        break;
     
   case 10:

          lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Anant");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
          funPassMessage("Mr.Maind Anant  is Driving Go-Kart ");
           break;

   case 11:

            lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Bagmar");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
            funPassMessage("Mr.Prashat Bagmar  is Driving Go-Kart ");
             break;

             case 15:

            lcd.clear();                 //clear the screen
        lcd.print("Hi Mr.Chaitanya");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
            funPassMessage("Mr.Chaitanya  is Driving Go-Kart ");
             break;
   default :Serial.println("\n  Registerd New Driver is driving a Go-Kart having id:");
            Serial.println(fingerID);
          
            lcd.clear();                 //clear the screen
        lcd.print("Hi New Dirver");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Ready For Drive");  //displaying the message on LCD
        delay(2000);
        lcd.clear();  
        lcd.print("Running....");  //displaying the message on LCD
            
         Serial.println("\n  Registerd New Driver is driving a Go-Kart having id:");
         Serial.println(fingerID);
           
  
  } //end of switch statement
  } //else
  

  //Serial.println("\n after to call Routine"); 
  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID); 
    //Serial.print(" with confidence of "); Serial.println(finger.confidence);
    return finger.fingerID; 
}//getfingerprintIDez

//----------------------------code to open and close latch
void fun_openCloseLatch()
{

  
  Serial.println("\n Dummy data:am opening or closing latch\n");

    //copy data from IR project
  if(pinLatch==LOW)
  {
    digitalWrite(pinLatch, HIGH); 
  }
  else
  {
    digitalWrite(pinLatch,LOW);
  }
}

//-------------------------cloud code to send datea on cloud 
void fun_sendDataToCloud()
{
  Serial.println("\n Dummy data :am sending data to cloud \n");
}

//---------------------------------------------keypad functions
/*
//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
  Serial.print("Pressed: ");
  Serial.println(eKey);
  switch (eKey){
    case '*': checkMasterPassword(); break;
    case '#': MasterfunReset();
              break;
    default: funTakeInputFromKeypad(eKey);
              break;
   // case 'A':checkForThumb();
    //break;          
     }
  }
}


//--------------------------fun-CheckPassword
void checkPassword(){
  
  
   if(password.evaluate())
    {
    Serial.println("Success");
    //call to registation
    loop_registration();
    funReset();
    //Add code to run if it works
  }
  else{
    Serial.println("Wrong");
    //add code to run if it did not work
  }

}//end of checkPassword

//-----------------------------checkMasterPassword()

//----------------------------------------
//-----------------funReset
void funReset()
{
    Serial.println("\n Normal password is resent sucessfully\n");
    password.reset();
    flagPassword=0;
    
}
*/
void checkMasterPassword()
{

  if(masterPassword.evaluate())
  {
       
  lcd.clear();               //clear the screen
  lcd.print("M.Pwd Sucess!!!");  //displaying the message on LCD
  delay(2000);
  lcd.clear(); 
  lcd.print("Go Cart will start!!!");  //displaying the message on LCD
  delay(2000);
   digitalWrite(pinLatch,HIGH); 
    lcd.clear(); 
  lcd.print("Running....!!!");  //displaying the message on LCD
  delay(3000);
   Serial.println("Master password sucessfull so start Go-cart( HIGH pin number 13)");
   funPassMessage("Alert...Go-Kart is sucessfully authonticated through Master password.Go card is going to start by Master Password!!! ");
   lcd.clear(); 
lcd.print("Go Cart will start!!!");  //displaying the message on LCD
delay(2000);
     masterPassword.reset();
    flagPassword=0;
    count=0;
    
  }
  else{
    Serial.println("Master password is wrong");

    lcd.clear();               //clear the screen
    lcd.print("Invalid Password");  //displaying the message on LCD
    delay(2000);
    masterPassword.reset();
    count=0;
    flagPassword=0;
    
    
    funWelcomeToGoCart();
    
    //add code to run if it did not work
  }

  
}
//-------

void MasterfunReset()
{
    
    masterPassword.reset();
    
    flagPassword=0;
    
    lcd.clear();               //clear the screen
    lcd.print("Password Reset!!!");  //displaying the message on LCD
    Serial.println("\n  Reset Done \n");
    count=0;
    delay(2000);
    funWelcomeToGoCart();
    
}
/*
//----------------------------funTakeInputFromKeypad()------
void funTakeInputFromKeypad(KeypadEvent eKey)
{

         lcd.clear();                    //clear the screen                    //done


      flagPassword=1; 
      masterPassword.append(eKey);
      count++;
 
     /*
   if(firstKey==0)
   {   // firstKey=1;
        // lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
         //lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
        
        lcd.clear();       ////display 9
        //delay(1000);
        flagPassword=1; 
         masterPassword.append(eKey);
          count++;
      lcd.print("*");
      delay(1000);
   }
   else
   {
      flagPassword=1; 
      masterPassword.append(eKey);
      count++;
   
      lcd.print("*");
      delay(1000);
   }

   
  switch(count)
  {


    case 1:
          lcd.print("*");
          digitalWrite(buzzerPin, HIGH);
          delay(1000);
          digitalWrite(buzzerPin, LOW);
          delay(1000);
          break;
    case 2:
            lcd.print("**");
            delay(1000);
            break;
    case 3: 
            lcd.print("***");
            delay(1000);
            break;
    case 4:
            lcd.print("*****");
            delay(1000);
             break;
    case 5:
            lcd.print("******");
            delay(1000);
 
            break;
    case 6:
            lcd.print("******");
            delay(1000);
            break;
    case 7: 
            lcd.print("*******");
            delay(1000);

            break;
    case 8: lcd.print("********");
            delay(1000);
            break;

   case 9:
          lcd.print("Pwd max len 8 char");
          delay(1000);
          break;
  } //end of switch
   
       // lcd.clear();                    //clear the screen                    //done
    //lcd.print("Enter Rem. Pwd");  //displaying the message on LCD
   // delay(1000);
 //  funWelcomeToGoCart();
*/
 
 
}//end of loop
//-------------------------------------------------------

void callTOSendMessage( int fingerID)
{
  SendMessage(fingerID);
}

 void SendMessage(int fingerID)
{

  //mySerialMessage.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  //delay(1000);  // Delay of 1000 milli seconds or 1 second

 // mySerialMessage.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number

  //delay(1000);


  
  
}

void SendMessageOfRegistration()
{

  mySerialMessage.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  //mySerialMessage.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number
  mySerialMessage.println("AT+CMGS=\"+919403561354\"\r"); // Replace x with mobile number
  delay(1000);
  
  mySerialMessage.write("\n Admin having ID 1 doing registration ");// The SMS text you want to send
  
  delay(100);
   mySerialMessage.println((char)26);// ASCII code of CTRL+Z
   delay(1000);
   Serial.println("message send to admin  successfully");

}
//--------------------------------------
void funPassMessage(char *str)
{
      Serial.println("\n Debug :am in funPassMessage ");
      Serial.println("\n Debug :i received string as follow");
      Serial.println(str);
      mySerialMessage.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      //mySerialMessage.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number
      mySerialMessage.println("AT+CMGS=\"+919403561354\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.println("\n Debug :am writing received message");
      mySerialMessage.write(str);// The SMS text you want to send
      delay(100);
      mySerialMessage.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
      Serial.println("\n message send to admin  successfully");
  }
//---------------------------------------


void SendMessageOfSystemStart()
{

  mySerialMessage.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
 delay(500);  // Delay of 1000 milli seconds or 1 second
  //mySerialMessage.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number
  mySerialMessage.println("AT+CMGS=\"+919403561354\"\r"); // Replace x with mobile number
  delay(500);
  
  mySerialMessage.write("\n Welcome to SNJB's WarHammer.\n Thumb Intialised..Display Intialised ...GSM Initialised...Now WarHammer is ready for Drive..."); // The SMS text you want to send
  
  delay(100);
   mySerialMessage.println((char)26);// ASCII code of CTRL+Z
   delay(500);
   Serial.println("Ready for drive message send to admin  successfully");

}
//--------------------------------------


void funWelcomeToGoCart()
{
lcd.clear();               //clear the screen
lcd.print("Welcome To Go-Kart!!!");  //displaying the message on LCD
delay(2000);
lcd.clear(); 
}


//--------------------------------------------------------------------------thumb 4

uint8_t readnumber(void) {   //fun1 registraion
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
/*
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
*/
//-----------------------------ldr

void testLDR()
{
sensorValueldr = analogRead(ldrPin);
serial.print("Sensorvalue is:");
seial.println(sensorValueldr);
if (sensorValueldr> threshold)
{
digitalWrite(lampPin, HIGH);
}
else
{
digitalWrite(lampPin, LOW);
}
}


void testPIR()
{
sensorValuePIR=digitalRead(PIRPin);
serial.print("PIR Sensorvalue is: ");
seial.println(sensorValuePIR);
if (sensorValuePIR> threshold)
{
digitalWrite(lampPin, HIGH);
}
else
{
digitalWrite(lampPin, LOW);
}
}//end of fun




