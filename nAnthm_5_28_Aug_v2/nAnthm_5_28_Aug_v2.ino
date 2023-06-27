
/* Sample code-1 */
/* Date and time functions using a DS3231 RTC connected via I2C and Wire lib  */
/* audio setting by Anant Maind

Change bit  resolution :8
change sampling rate : 11025
Change audio Channels :mono
link :
https://audio.online-convert.com/convert-to-wav


testPravinMicTestWaw
testPravinSDAmplifierSpeakerWaw
testPravinTimeTestWaw

*/
//---------------- password and keypad

//#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip







//--------
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

RTC_DS3231 rtc;
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560  //1
#include <TMRpcm.h>           //  also need to include this library...  //2
#include <SPI.h>                                                        //3
TMRpcm tmrpcm;   // create an object for use in this sketch             //4

// with the arduino pin number it is connected to
const int rs = 49, en =47, d4 = 45, d5 = 43, d6 = 41, d7 = 39;    //need to edit as per our requirement  *****
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//for RTC
String strhh,strmm,strss;
int valueOfModePin=0;
int modePin=10;

int i=1;

//-------------------------------before 928 code at day time set to 0 zero



//------------------------------- after 928 code at afternnon time set to 1 one 





//--------------------------------------------------------------------------
void setup ()
{

// pinMode(modePin,INPUT_PULLUP); 
  pinMode(modePin,INPUT); 
//------------------------------------------RTC Setup
  Serial.begin(9600);
  Serial.println("\n Welocme To Lecture Announcement Project \n");
  delay(2000); // wait for console opening

     lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8

    //--------------------------------------------------------LCD module setup 
      // set up the LCD's number of columns and rows:
            lcd.begin(16, 1);
            delay(1000);
           Serial.println("LCD module is Ok...."); 
           lcd.print("initialising......");
            delay(2000);
        

    //clear the screen
     lcd.clear();       ////display 9
    lcd.print("Welcome TO SNJB");  //displaying the message on LCD
    delay(2000);
  
    lcd.clear();       ////display 9
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.print("Develop By COMP");  //displaying the message on LCD
     delay(1000);
     lcd.clear();       ////display 9
     
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.print("R and D Lab");  //displaying the message on LCD
   
    delay(2000);
    
  

  if (! rtc.begin())
  {
    Serial.println(" Couldn't find RTC ");
    while (1);
  }
    else
   {
      Serial.println("RTC Module is ok..."); 
   }
  if (rtc.lostPower())
  {
    Serial.println(" RTC lost power, let’s set the time! ");
    // January 21, 2014 at 3am you would call:
   // rtc.adjust(DateTime(2018, 20, 03, 02, 01, 00));
   // rtc.adjust(DateTime(2018, 1,16 , 5, 8, 30)); //set current time and cut paiste same line outside of for loop
  }
//   rtc.adjust(DateTime(2020,8,28, 10,02, 00));   // to renter time *************************************************************
 

 //------------------------------------------------------------Sound module setup
 tmrpcm.speakerPin = 46; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc  //5

  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD card module not working properly");  
    return;   // don't do anything more if not
  }

  else
  {

     Serial.println("SD Card module is Ok...."); 
     Serial.println("Playing testing sound ....."); 
     tmrpcm.play("Test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6 
  }

  
void rtcchange()
{
  int d,m,y,hh,mm,ss;
  delay(1000);
  Serial.println("Enter the Date Details:");
  Serial.println("Enter the Day DD:");
  d=(int)Serial.read();
  Serial.println("Enter the Month MM:");
  m=(int)Serial.read();
  Serial.println("Enter the Year YYYY:");
  y=(int)Serial.read();
  Serial.println("Enter the Time Details:");
  Serial.println("Enter the HH:");
  hh=(int)Serial.read();
  Serial.println("Enter the MM:");
  d=(int)Serial.read();
  Serial.println("Enter the SS:");
  d=(int)Serial.read();
  rtc.adjust(DateTime(y, m, d, hh, mm, ss));  
 //rtc.adjust(DateTime(2018, 11, 03, 12, 22, 0));  
}

//-----------------------------------
void loop ()
{

     // tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
     //  tmrpcm.play("na.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
      
      //delay(65000);   


   //   testRecording();
 Serial.println("\n am in loop");   

  funReadPushButtonMode();
 Serial.println("\n am below funReadPushButtonMode");   

  if (Serial.available() > 0) {
  int incomingByte; 
                // read the incoming byte:
                incomingByte = Serial.read();
                if(incomingByte==5) 
                {
                  rtcchange();
                
              }
                // say what you got:
        }

        Serial.println("\n am below serial if");   

 //showTimeOnSerial();
 showTimeOnLCD();
 Serial.println("\n am belowshow time lcd");   
//--------------------------time to string 

 DateTime now = rtc.now();

String  hm ;
int k=0;
Serial.print("\n This is time of RTC ");
showTimeOnSerial();
strhh =  String(now.hour());
strmm =  String( now.minute());
 strss =  String( now.second());
//hm=strhh+strmm+strss;
hm=strhh+strmm;



//hm ="123456";
//Serial.print(hm);
//hm.remove(5);   // Remove from from index=3 through the end of the string
Serial.print(" Check Time after triming-------------------------------------------------------------------------------------------------");
Serial.print(hm);
delay(1000);
//------------------------------------------------------------------------------------------
int hmInt=hm.toInt();
//Serial.print("Converting and displyingtime string into int \n ");
//Serial.print(hmInt);
  //-------------------------------------
//hmInt=925;  //for testing 1 remove it after testing
//if(hmInt==9251 || hmInt==9281 || hmInt==9301 || hmInt==10301 || hmInt==11301 || hmInt==12151 || hmInt==1151 || hmInt==2151 || hmInt==2301 || hmInt==3301 || hmInt==4301 )
// true_time();
    //  if(true_time())  //****
     // {
//while(i<11)
//{
Serial.print("Value of hmint in integer is "+hmInt);
 Serial.println("\n am above swith case ");   
switch (hmInt) {    //to convert testing project just change hmInt to i
   
    case 928 :    // your hand is close to the sensor

        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("gathered Ampi");
        tmrpcm.play("na.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
        delay(65000);   

        delay(61000);//maintain minute    
     break;
     //---------------------------------------------------------------------------------------------------------first lect  
   /* case  101:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------in 10.01 case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("First Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
         delay(61000);//maintain minute    
      break;
//----------------------------------------------------------------------------------------------------------------second lect
     case  1051:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------in 10.01 case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Second Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
        delay(61000); //maintain minute    
      break;
     
   //-------------------------------------------------------------------------------------------------------   Lunch Break

   case  1131:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------inLuch break case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Lunch Break Started");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
        delay(61000); //maintain minute    
      break;


   //----------------------------------------------------------------------------------------------- Third lecture started

     case  1231:    // your hand is a few inches from the sensor //----------------
     Serial.println("--------------in 10.01 case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Third Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
         delay(61000);//maintain minute    
      break;
//------------------------------------------------------------------------------------------  Fouth lecutre started
case  1321:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------Fourth lecture case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fourth Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
       delay(61000); //maintain minute    
      break;
          
//---------------------------------------------------------------------------------Tea Break  started

case 141 :    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------in 10.01 case  entered");
       showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Tea Break Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
        delay(61000); //maintain minute    
      break;

case  1411:    // your hand is a few inches from the sensor //----------------Fifth lecture started
     Serial.println("--------------in Fifth lecture started  case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fifth Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
        delay(61000); //maintain minute    
      break;
     
     //-------------------------------------------------------------------------------Sixth lecture started

     
case 1451  :    // your hand is a few inches from the sensor //----------------sixth lecture started
     Serial.println("--------------in sixth lecture started  case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fifth Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
       delay(61000); //maintain minute    
      break;

 case 1630  :    // your hand is a few inches from the sensor //----------------sixth lecture over
     Serial.println("--------------in sixth lecture started  case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fifth Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
        delay(61000); //maintain minute    
      break;    

//------------------------------------------------------------------------------------------------------    
case 1640  :    // your hand is a few inches from the sensor //----------------clg over
     Serial.println("--------------in sixth lecture started  case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fifth Lect Start");
        tmrpcm.play("testPSD.wav");   //----------- change this file on 28 aug 
        delay(4000);
         delay(61000); //maintain minute    
      break;*/
     
//--------------------------------------------------------------------------------------------------------------***************Testing
}
}
}
