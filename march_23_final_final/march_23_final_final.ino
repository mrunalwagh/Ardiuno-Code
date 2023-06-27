
/* Sample code-1 */
/* Date and time functions using a DS3231 RTC connected via I2C and Wire lib  */
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

RTC_DS3231 rtc;
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560  //1
#include <TMRpcm.h>           //  also need to include this library...  //2
#include <SPI.h>                                                        //3
TMRpcm tmrpcm;   // create an object for use in this sketch             //4

// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 5, d5 = 6, d6 = 3, d7 = 2;    //need to edit as per our requirement  *****
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//for RTC
String strhh,strmm,strss;

int i=1;
void setup ()
{

 
//------------------------------------------RTC Setup
  Serial.begin(9600);
  Serial.println("\n Welocme To Lecture Announcement Project \n");
  delay(2000); // wait for console opening
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
    rtc.adjust(DateTime(2018, 20, 03, 02, 01, 00));
   // rtc.adjust(DateTime(2018, 1,16 , 5, 8, 30)); //set current time and cut paiste same line outside of for loop
  }

  //--------------------------------------------------------LCD module setup 
      // set up the LCD's number of columns and rows:
            lcd.begin(16, 1);
            delay(1000);
           Serial.println("LCD module is Ok...."); 
           lcd.print("initialise......");
            delay(2000);
         // Print a message to the LCD.
          lcd.print("Prof.Maind A.L \n ");
             delay(1000); 

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
     // tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6 
  }

   //  tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //6



      
}
//------------------------------------
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

//-----------------------------------
void loop ()
{

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
 //showTimeOnSerial();
 showTimeOnLCD();

//--------------------------time to string 

 DateTime now = rtc.now();

String  hm ;
int k=0;
Serial.print("\n This is time of RTC ");
showTimeOnSerial();
strhh =  String(now.hour());
strmm =  String( now.minute());
 strss =  String( now.second());
hm=strhh+strmm+strss;
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
hm.remove(5);   // Remove from from index=3 through the end of the string
Serial.print("Time after triming");
Serial.print(hm);
//delay(5000);
//------------------------------------------------------------------------------------------
int hmInt=hm.toInt();
//Serial.print("Converting and displyingtime string into int \n ");
//Serial.print(hmInt);
  //-------------------------------------
//hmInt=925;  //for testing 1 remove it after testing
//if(hmInt==9251 || hmInt==9281 || hmInt==9301 || hmInt==10301 || hmInt==11301 || hmInt==12151 || hmInt==1151 || hmInt==2151 || hmInt==2301 || hmInt==3301 || hmInt==4301 )
// true_time();
if(true_time())
{
//while(i<11)
//{
Serial.print("Value of hmint is"+hmInt);
    
switch (hmInt) {    //to convert testing project just change hmInt to i
 /*   case 1:    // your hand is on the sensor    //kept just for testing
    Serial.print("we are in case 1");
      
      delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Good Morning All. All of You please gathered in open ampitheter");
       tmrpcm.play("gatherA.wav");
      //  tmrpcm.play("VoiceA.wav");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      
      break;
    case 2:    // your hand is close to the sensor   //kept jsut for testing
     delay(30000);
      Serial.println("All of You please gathered in open ampitheter");
       tmrpcm.play("firstC.wav");
         
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("All of You please gathered in open ampitheter");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      break;
      break;
   */   
    case 9251 :    // your hand is close to the sensor
     
      Serial.println("All of You please gathered in open ampitheter");
       tmrpcm.play("gatherA.wav");
         delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("All of You please gathered in open ampitheter");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      break;
    
    case 9281 :    // your hand is a few inches from the sensor
      Serial.println("All student go to respective class room");
       tmrpcm.play("goB.wav");
      delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("All student go to respective class room");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      
      break;
    case 9301 :    // your hand is nowhere near the sensor
      Serial.println("First Lecture started");
      //3_first_9_30
       tmrpcm.play("firstC.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("First Lecture started");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      break;
     //-------------------------------------------------------
      case 10301 :    // your hand is on the sensor
      Serial.println("Second Lecture started");
      tmrpcm.play("secondD.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Second Lecture started");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
    break;
      //-------------------------------------
      





      //---------------------------------------
    case 11301 :    // your hand is close to the sensor
      Serial.println("Second lecture is over,Resses Time.");
       tmrpcm.play("secondOverE.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Second lecture is over,Resses Time");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
     break;
    case 12151 :    // your hand is a few inches from the sensor
      Serial.println("Third lecture Started");
      tmrpcm.play("thirdF.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Third lecture Started");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      break;
    case 1151 :    // your hand is nowhere near the sensor
      Serial.println("Fourth Lecture Started");
       tmrpcm.play("fourthG.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Fourth Lecture Started");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      break;

       case 2151 :    // your hand is a few inches from the sensor
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Fourth Lecture is over.Tea Time");
       tmrpcm.play("teaTimeH.wav");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      Serial.println("Fourth Lecture is over.Tea Time");
      break;
      //--------------------
    case 2301 :    // your hand is nowhere near the sensor
      Serial.println("Fift Lecture Started");
      tmrpcm.play("fifthI.wav");
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Fift Lecture Started");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
     break;
      //----------------------------
       case 3301 :    // your hand is nowhere near the sensor
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("Sixth lecture is started");
      tmrpcm.play("sixthJ.wav");
      

      delay(3000);
      showTimeOnLCD();
      delay(3000);
      Serial.println("Sixth lecture is started");
     break;

       case 4301 :    // your hand is nowhere near the sensor
       delay(1000);
      showTimeOnSerial();
       lcd.begin(16, 1);
      lcd.print("college is over");
       tmrpcm.play("collegeOverK.wav");
      delay(3000);
      showTimeOnLCD();
      delay(3000);
      Serial.println("college is over");
      break;


      
  }//end of switch
  delay(1);        // delay in between reads for stability
showTimeOnLCD();

//  i=i+1;
// }//end of while 
} //end of loop
}//end of if


//------------------------
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
  delay(1000);
 
  
}

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
