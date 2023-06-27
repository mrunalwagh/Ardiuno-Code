 //  node mcu id  :   5c5e8c1406ebc82b0348757b  
//------------------------------------------------------display
#include<LiquidCrystal.h>    //display 1

int rs=26;  //  display 2
int en=28;  //  display 3
int d4=30;  //  display 4
int d5=32;  //  display 5
int d6=34;  //  display 6
int d7=36;  //  display 7


Int buzzerPin = 40;  
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);   //display 7// configure the pin RS,enable,D4,D5,D6,D7  resp.

int count=0;
int firstKey=0;

//------------------------------------------------------------
#include <Adafruit_Fingerprint.h>

//#include <SoftwareSerial.h>
//#include "SoftwareSerial.h"


//#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>  //"" for node mcu
SoftwareSerial mySerial(10,11); //2 3 for uno//gpio 13 =rx(nodemcu pinD7),gpio 15=tx(nodemcu pin D8)
SoftwareSerial mySerialMessage(52, 53);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial,1337);
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
Password masterPassword = Password("159357");
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


    //---------------buzzer
    pinMode(buzzerPin, OUTPUT);        

   //-------------------
     lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9

    //clear the screen
    lcd.print("Welcome Go-Kart");  //displaying the message on LCD

   //-------------------

  mySerialMessage.begin(9600);
  
  Serial.begin(9600);  //for node mcu921600
   delay(100);
//------for testing
   SendMessageOfSystemStart();
   //Serial.println("\n am entering  setup\n");
  pinMode(pinLatch,OUTPUT);  //setting latch output
          // Serial.swap();
          //Serial.begin(100000);
          //Serial.setDebugOutput(true);
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nSNJB R and D Finger Print System:");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("\n fingerprint sensor Found Sucessfully.You can Proceed!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  //Serial.println("\n am exiting setup\n");
  //--------------keypad setup
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad


}


uint8_t readnumber(void) {   //fun1 registraion
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

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
  
  
 
}//end of loop
      
//----
void loop_registration()
{
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
lcd.print("Welcome To Go-Kart!!!");  //displaying the message on LCD
delay(2000);
lcd.clear(); 
}
