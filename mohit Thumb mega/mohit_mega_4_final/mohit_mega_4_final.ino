 //  node mcu id  :   5c5e8c1406ebc82b0348757b  
//------------------------------------------------------display
#include<LiquidCrystal.h>    //display 1
#include <RTClib.h>
RTC_DS3231 rtc;
int rs=7;  //  display 2
int en=6;  //  display 3
int d4=5;  //  display 4
int d5=4;  //  display 5
int d6=3;  //  display 6
int d7=2;  //  display 7

int sensorValuePIR;
int sensorValueLDR;
int LDRPin=A0;
int PIRPin=21;
int lampPin=22;
int buzzerPin = 40;  
int threshold=10;
String datavalues;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);   //display 7// configure the pin RS,enable,D4,D5,D6,D7  resp.
int rollNo=1;
//-----------------

String strdd;
String strmonth;
String stryy;
String strhh;
String strmm;
String strss;
 
String dhm ;
//--------------

int count=0;
int firstKey=0;


//------------------------------------------------------------
#include <Adafruit_Fingerprint.h>   //thum1 

//#include <SoftwareSerial.h>
//#include "SoftwareSerial.h"


//#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>  //"" for node mcu
SoftwareSerial mySerial(52,53); //2 3 for uno//gpio 13 =rx(nodemcu pinD7),gpio 15=tx(nodemcu pin D8)   //thumb 2
SoftwareSerial mySerialMessage(54, 51);
SoftwareSerial mton(10,11); //52 rx ->D6 53 tx     //52 53 replace by 10 D6   11 D5 of thumb
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial,1337);
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
//-----------------Declaration ----
int pinLatch=13;
void loop_verification();
uint8_t id;
char choice;
int fingerID;
//---------------------------keypad declaration
#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

//Password password = Password("1334");
Password masterPassword = Password("123456");
int flagPassword=0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'} 
};


//byte rowPins[ROWS] = { 11,10,9,8 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
//byte colPins[COLS] = { 7,6,5,4 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



//----------------------------------------

void setup()  
{

   pinMode(LDRPin, INPUT); 
   pinMode(PIRPin, INPUT); 
   pinMode(lampPin, OUTPUT); 
    //---------------buzzer
    pinMode(buzzerPin, OUTPUT);        
mton.begin(9600);
   //-------------------
     lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9

    //clear the screen
   // lcd.print("Welcome to SMart ");  //displaying the message on LCD
  showOnLCDGeneral("Welcome To ","Smart Class");
   delay(2000);

   //-------------------

  mySerialMessage.begin(9600);
  
  Serial.begin(9600);  //for node mcu921600
   delay(100);
//------for testing
  // SendMessageOfSystemStart();
   //Serial.println("\n am entering  setup\n");
  pinMode(pinLatch,OUTPUT);  //setting latch output
          // Serial.swap();
          //Serial.begin(100000);
          //Serial.setDebugOutput(true);
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nSNJB R and D Finger Print System:");//----------------------------------------------thumb 3

  // set the data rate for the sensor serial port
 

  //--------------------------------------------------------------------------------------------------------------

  //Serial.println("\n am exiting setup\n");
  //--------------keypad setup
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
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
    // rtc.adjust(DateTime(2020,9,11, 16,53,00));   // to renter time *************************************************************

  }
  
    //rtc.adjust(DateTime(2020,9,11, 16,53,00));   // to renter time *************************************************************
 Serial.println(" ibelow date adjusted ");
 String strTime=findDHM();
 showOnLCDGeneral("Time",dhm);
 Serial.println(strTime);
//-------------------

 finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("\n fingerprint sensor Found Sucessfully.You can Proceed!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    showOnLCDGeneral("Finger Not Match","Try Again");
    while (1) { delay(1); }
  }
  
 //---------------------



}//end of setup

//--------------------------------------------------------------------------thumb 4

uint8_t readnumber(void) {   //fun1 registraion
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}


//----------------------------------------------------------------

void loop()                     // run over and over again   //fun2 registration
{

   
  Serial.flush();
  while (!Serial)  // For Yun/Leo/Micro/Zero/...
  delay(100);  // if(Serial.available()>0)
  //---------------------------------------keypad loop
   if(flagPassword==0)
  {
    
    Serial.println("\nAdmin will Enter Password (* for Verify Password, # for Reset Password) \nUser will give Thumb");
    keypad.getKey();
    loop_verification();
    delay(300);
  }
   keypad.getKey();
    
   //  showOnLCDGeneral("am in ","loop Verification");
      Serial.println("am calling take attenance ");
          
     
     takeAttendance();

      
    
  
      
  

 //  rollNo=-1;
   
 testLDR();
 testPIR();
 
}//end of loop
      
//----

//--------------------------------------------------------------------------thumb 5
void loop_registration()
{
  char key;
 // Serial.println("Ready to enroll a fingerprint!");
  Serial.println("\n Enter ID (from 2 to 255) to be assign: \n");
  showOnLCDGeneral("Enter ID From","2 to 255");
  key=keypad.getKey();
  while(!key)
  {
    Serial.println("\n Enter Key :");
    showOnLCDGeneral("Enter Key","");
    key=keypad.getKey();
    delay(1000);
  }
  
  Serial.println("\nAm printing key value");
  showOnLCDGeneral("Enterd Key is ","");
  Serial.println(key);
  showOnLCDGeneral(String(key),"");
  delay(2000);
  id=(int)key-48;
  Serial.println("\nAm printing key value in int");
  Serial.println(id);
  //id = readnumber();
  if (id == 0) { // ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  showOnLCDGeneral("Enrolling ID","");
  Serial.println(id);
  showOnLCDGeneral(String(id),"");
  while(!getFingerprintEnroll() );

}
//----

uint8_t getFingerprintEnroll() {
int flagExit=0;
while(flagExit==0)
{
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  showOnLCDGeneral("Waiting for Finger","enroll");
  Serial.println(id);
  showOnLCDGeneral(String(id),"");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      showOnLCDGeneral("Image Taken","");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      showOnLCDGeneral("Communication Error","");
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
  showOnLCDGeneral("Remove Finger"," ");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  showOnLCDGeneral("Place Same Finger","again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      showOnLCDGeneral("Image Taken","");
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
    showOnLCDGeneral("Thumb stored ","Sucess");
    flagExit=1;
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
}//end of while
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
     delay(2000);
     Serial.println("\n i received from getFingerPrintIDez");
    // Serial.println(id1);
   //  delay(3000);  ///remove delay
     //return(id1);     
}  //loop verification

void getFingerprintIDez()
{   //-------------------------------------work

  
   lcd.clear();
    showOnLCDGeneral("Waiting For","Thumb");
    delay(2000);
   //showOnLCDGeneral("am in","getFingerPrintIDez"); 
  Serial.println("\n am enter in getFingerPrintIDez");
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

     // found a match!
  Serial.print("USER ID:"); Serial.print(finger.fingerID);
  showOnLCDGeneral("Roll No",String(finger.fingerID)); 
  showOnLCDGeneral("Login       ","   Successfully");
  Serial.println("\n Login Successfully....");
  //---
 // lcd.clear();               //clear the screen
 // lcd.print("Login Sucessfull");  //displaying the message on LCD
  //delay(2000);
 // funWelcomeToGoCart();
  //-----
  
  
  Serial.print("USER ID:"); Serial.print(finger.fingerID);
 //  showOnLCDGeneral("Roll No", String(finger.fingerID)); 
  //showOnLCDGeneral("Login       ","   Successfully");
  Serial.print("\nMatched With Confidance level: "); Serial.println(finger.confidence);


  //--------------

   if(finger.fingerID!=-1)
   {   
     
        //delay(3000);
      
    // sendValues(t,range,dhm);  //void sendValues(int float temp1,int range1)
       String dhm1=findDHM();
      
     sendValues(finger.fingerID,dhm1);  //void sendValues(int float temp1,int range1)
     
     showOnLCDGeneral("Att. sending to","cloud done");
     showOnLCDGeneral("Wait..."," ");
   }
   else
   {
    Serial.println("Value was -1 so not send");
   }


  //-------------
   
  //Serial.println("\n Relay pin 13 set to high ");  
  digitalWrite(pinLatch, HIGH); 
  if(finger.fingerID==1)
  {
      
      Serial.println("\n Welcome Admin !!!");
      showOnLCDGeneral("Welcome","Admin");
      Serial.println("\n You can Register New user"); 
      showOnLCDGeneral("You Can Register","New User");
      SendMessageOfRegistration();

      loop_registration();
  }
  else
  {
 /*
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

    */

   Serial.println("am returning finger id from getfingerprintIDez------------------------");
   Serial.println(finger.fingerID);
    delay(1000);
    
    //return finger.fingerID; 
  }
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

/*
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

   */
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

 
}  //end of fun
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
lcd.print("Welcome !!!");  //displaying the message on LCD
delay(2000);
lcd.clear(); 
}

//-------------------------

void testPIR()
{
  sensorValuePIR=digitalRead(PIRPin);
  Serial.print("PIR Sensorvalue is: ");
  Serial.println(sensorValuePIR);
  if (sensorValuePIR==1)
  {
    showOnLCDGeneral("Someone is in","Room");
    digitalWrite(lampPin, HIGH);
  }
  else
  {
    digitalWrite(lampPin, LOW);
  }
}//end 

//--------------------------------------------


void testLDR()
{
  sensorValueLDR = analogRead(LDRPin);
  Serial.print("Sensorvalue of LDR is:----------------------------------------------------");
  delay(1000);
  Serial.println(sensorValueLDR);
  if (sensorValueLDR< threshold)
  {
    showOnLCDGeneral("Below LDR Thr ","Light On");
  digitalWrite(lampPin, HIGH);
  }
  else
  {
  digitalWrite(lampPin, LOW);
  }
}
//---------------------------------
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
     lcd.begin(16,2);
     lcd.clear();       ////display 9
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print(title);  //displaying the message on LCD
        lcd.setCursor(0,1); 
         
     lcd.print(msg);  //displaying the message on LCD
     delay(2000);
}
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
//--------------------------------------takeAttendance

void takeAttendance()
{
 
  
   
   loop_verification();   
Serial.println("received from loop verification ");
//Serial.println(id1);
delay(3000);  //remove delay
     
   

}
//-------------------------------------------

String findDHM()
{
  
  DateTime now = rtc.now();


  Serial.print("\n This is time of RTC ");
  strdd=String(now.day());
  strmonth=String(now.month());
  stryy=String( now.year());
  strhh =  String(now.hour());
  strmm =  String( now.minute());
  strss =  String( now.second());
 
  dhm=strdd+":"+strmonth+":"+stryy+" "+strhh+":"+strmm+":"+strss;

 // showOnLCDGeneral("Time Stamp",dhm);
  Serial.println("Time is ");
  Serial.println(dhm);
  return(dhm);

} //end of find dhm


