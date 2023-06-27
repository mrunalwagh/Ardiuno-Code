
/* Sample code-1 */
/* Date and time functions using a DS3231 RTC connected via I2C and Wire lib  */


/*Change bit  resolution :8
change sampling rate : 11025
Change audio Channels :mono
link :
https://audio.online-convert.com/convert-to-wav


testPravinMicTestWaw
testPravinSDAmplifierSpeakerWaw
testPravinTimeTestWaw*/

#include <Wire.h>
#include <RTClib.h>


RTC_DS3231 rtc;
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560  //1
#include <TMRpcm.h>           //  also need to include this library...  //2
#include <SPI.h>                                                        //3
TMRpcm tmrpcm;   // create an object for use in this sketch             //4

// with the arduino pin number it is connected to
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


//for RTC
String strhh,strmm,strss;
int valueOfModePin=0;
int modePin=10;

int i=1;
//int buz = D8;
//-------------------------------before 928 code at day time set to 0 zero
//------------------------------- after 928 code at afternnon time set to 1 one 

void setup ()
{

// pinMode(modePin,INPUT_PULLUP); 
  pinMode(modePin,INPUT); 
//  pinMode(D8,OUTPUT);
//------------------------------------------RTC Setup
  Serial.begin(9600);
   Wire.begin(2,0);
  lcd.init();
  lcd.backlight();
  Serial.println("\n Welocme To Lecture Announcement Project \n");
  delay(2000); // wait for console opening

    lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
           Serial.println("LCD module is Ok...."); 
           lcd.print("initialising......");
            delay(2000);
        

    //clear the screen
     lcd.clear();       ////display 9
    lcd.print("Welcome TO SNJB");  //displaying the message on LCD
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
   // rtc.adjust(DateTime(2022, 20, 03, 02, 01, 00));
   // rtc.adjust(DateTime(2018, 1,16 , 5, 8, 30)); //set current time and cut paiste same line outside of for loop
  }
   rtc.adjust(DateTime(2020,9,28,9,57,15));   // to renter time *************************************************************
 

 //------------------------------------------------------------Sound module setup
// tmrpcm.speakerPin = 46; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc  //5

  Serial.begin(9600);
////  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
//    Serial.println("SD card module not working properly");  
//    return;   // don't do anything more if not
//  }
//
//  else
//  {
//
//     Serial.println("SD Card module is Ok...."); 
//     Serial.println("Playing testing sound ....."); 
//     // tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6 
//  }

   //  tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6

       //   tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****

  //check wheather test button enable 

  //---------------------------------------------

  //   tmrpcm.play("na.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
    // delay(65000);

 /*        
funReadPushButtonMode();
  if(testButton==1)
  {

     test();
  }
  
 */
      
}//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//rtc change time
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

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop ()
{

     
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
//delay(1000);
//Serial.print(hm);
//Serial.print("Displaying hh and hm in string ");
//Serial.print(strhh);
//Serial.print(strmm);
//Serial.print("Displaying string after concatnation ");
//Serial.print(hm);
//----------------------------------------testing purpose


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


 
    case 9281:    // your hand is close to the sensor

        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("gathered Ampi");
       tmrpcm.play("na.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
        void buzzer();
        delay(61000);    
     break;
     //---------------------------------------------------------------------------------------------------------first lect  
    case  10301:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------in 10.01 case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("First Lect Start");
        //tmrpcm.play("FirstLS.wav");   //----------- change this file on 28 aug 
        //delay(4000);
        void buzzer();
        delay(61000);//maintain minute    
      break;

   case  11301:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------inLuch break case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Lunch Break Started");
        //tmrpcm.play("SecLOTeaBreak.wav");   //----------- change this file on 28 aug 
        //delay(4000);*/
        void buzzer();
        delay(61000); //maintain minute    
      
      break;


   //----------------------------------------------------------------------------------------------- Third lecture started

     case  12151:    // your hand is a few inches from the sensor //----------------
     Serial.println("--------------in 10.01 case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Third Lect Start");
        //tmrpcm.play("ThirdLS.wav");   //----------- change this file on 28 aug 
        //delay(4000);
        void buzzer();
         delay(61000);//maintain minute    
      break;
//------------------------------------------------------------------------------------------  Fouth lecutre started
     case  14151:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------Fourth lecture case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fourth Lect Start");
        //tmrpcm.play("FourthLS.wav");   //----------- change this file on 28 aug 
        //delay(4000);
        void buzzer();
       delay(61000); //maintain minute    
      break;
          
//---------------------------------------------------------------------------------Tea Break  started

case 14501:    // your hand is a few inches from the sensor //----------------Time testing 
     Serial.println("--------------in 10.01 case  entered");
       showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Tea Break Start");
        //tmrpcm.play("Teabreak.wav");   //----------- change this file on 28 aug 
        //delay(4000);
        void buzzer();
        delay(61000); //maintain minute    
      break;

case  16301:    // your hand is a few inches from the sensor //----------------Fifth lecture started
     Serial.println("--------------in Fifth lecture started  case  entered");
        showTimeOnLCD();
        showTimeOnSerial();
        showMsgOnLCD("Fifth Lect Start");
        //tmrpcm.play("FifthLS.wav");   //----------- change this file on 28 aug 
        //delay(4000);
        void buzzer();
        delay(61000); //maintain minute    
      break;
     
   

 default : Serial.println("\n am in default case");
      
  }//end of switch
         // delay in between reads for stability
showTimeOnLCD();

//  i=i+1;
// }//end of while 
  //} //end of if
}//end of loop


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void showTimeOnLCD()
{
    DateTime now = rtc.now();
     lcd.begin(16, 1);
//lcd output 
  lcd.print(now.hour());   //Serial.print();
  lcd.print(':');          //Serial.print();
  lcd.print(now.minute());  // Serial.print();
  lcd.print(':');          //Serial.print();
  lcd.print(now.second());  //Serial.print();
  //lcd.print("   M:");          //Serial.print();
  //lcd.print("Test");  //Serial.print();


if(valueOfModePin==1)    //testing mode
{
 // lcd.setCursor(1,1);       // set the cursor at position (C1,R0)  //display 8
  lcd.print(" M:");          //Serial.print();
  lcd.print("Test");  //Serial.print();

 //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
}
else if(valueOfModePin==0)  // working mode
{
   //lcd.setCursor(1,1);       // set the cursor at position (C1,R0)  //display 8
   lcd.print(" M:");          //Serial.print();
  lcd.print("Work");  //Serial.print();
}

  delay(1000);
 // lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
void showTimeOnSerial()
{

   DateTime now = rtc.now();

  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();

}

boolean true_time()
{
  //if(hmInt==9251 || hmInt==9281 || hmInt==9301 || hmInt==10301 || hmInt==11301 || hmInt==12151 || hmInt==1151 || hmInt==2151 || hmInt==2301 || hmInt==3301 || hmInt==4301 )

  if((strhh.equals("9") && strmm.equals("25") && strss.equals("1")))
  {
    return true;
  }
  else if(strhh.equals("9") && strmm.equals("28") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("9") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("10") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("11") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("12") && strmm.equals("15") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("1") && strmm.equals("15") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("2") && strmm.equals("15") && strss.equals("1"))
  {
    return true;
  }// hmInt==2301 || hmInt==3301 || hmInt==4301 )

  else if(strhh.equals("2") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("3") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else if(strhh.equals("4") && strmm.equals("30") && strss.equals("1"))
  {
    return true;
  }
  else
  {
    return false;
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------test function
void test()
{

// tmrpcm.play("na.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
  delay(65000);   

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------



void  funReadPushButtonMode()
{

//button press then read value from eeprom and invert it and write it back to eeprom)
  valueOfModePin = digitalRead(modePin);

  Serial.println("\n am inf button mode fucntion----------------------------");
  Serial.println("---------------------------------------------------------------------------valueOfModePin");
   Serial.println(valueOfModePin);
   
     delay(200);
  if (valueOfModePin==0) // && prevState==2) // working mode
  {
       // working mode
  }
  else if(valueOfModePin==1)// && prevState==1)
  {
         
         do{  
           
           //lcd screen : Testing MOde : IF sound Then Sucess IF No Sound Then Test Failed");
           Serial.println("\Testing   Amplifier ok  speaker ok SD card OK ");
           //lcd scree
            lcd.begin(16, 1);
            delay(1000);
           Serial.println("LCD module is Ok...."); 
           lcd.print("LCD SD Spkr OK..");
            delay(1000);
            //play audio file
              Serial.println("testringSpeakerOk file is will get played...."); 
            // tmrpcm.play("testingSpeakerOk_waw.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****

        //    tmrpcm.play("testPravinSDAmplifierSpeakerWaw.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****
//                 tmrpcm.play("testPSD.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6  //****

            //  testingTesting _waw
             delay(4000);
            Serial.println("You can change testing mode to Normal mode by sliding Mode button   and reset system ");
           // lcd screen
            //play audio file
            //delay(5000);
            showTimeOnLCD();
            delay(1000);

               valueOfModePin = digitalRead(modePin);

           }while(valueOfModePin==1);
            Serial.println("---------------------------------------------------------------------------valueOfModePin");
   Serial.println(valueOfModePin);
   
  }
       
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
} 
 void showMsgOnLCD(String  str)
 { 
        lcd.begin(16, 1);
        lcd.print(str);
        delay(1000);
        Serial.println(str);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 /*void buzzer(){
  
 
     digitalWrite(D8,HIGH);
     delay(500);
     digitalWrite(D8,LOW);
     delay(200);
     digitalWrite(D8,HIGH);
     delay(500);
     digitalWrite(D8,LOW);
     delay(200);
     digitalWrite(D8,HIGH);
     delay(500);
     digitalWrite(D8,LOW);
     digitalWrite(D8,HIGH);
     delay(200);
     digitalWrite(D8,LOW);

 }*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
