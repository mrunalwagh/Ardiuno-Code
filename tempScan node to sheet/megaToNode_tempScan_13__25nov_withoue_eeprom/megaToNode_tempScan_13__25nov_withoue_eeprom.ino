#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560  // s1
#include <TMRpcm.h>           //  also need to include this library...  //s2
#include <SPI.h>  
//#include <Adafruit_GFX.h> //s3
TMRpcm tmrpcm;   // create an object for use in this sketch             //s4

//#include <SoftwareSerial.h>        //mton0
//-----------------------------------------------------------makuna declaration
#include <SoftwareSerial.h>
//#include <DFMiniMp3.h>
//SoftwareSerial mton(A8,A9);        //mton1 rx tx      A8->D6     A9->D5
//---------------------------------------------makuna class

//------------------------------------------------------------------------makuna object creation

//---------------------------------------------------------------------------------------------



//-----------------------------eeprom declaration

#include <EEPROM.h>  
//------------------------------rtc declaration  
#include <Wire.h>
#include "RTClib.h"
//---------------------------- temp declaration
#include <Wire.h>
//#include <Adafruit_MLX90614.h>
//---------------------------
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

uint16_t version = MCUFRIEND_KBV_H_;
//measure upt0 55mm
int entryDoorStart=56,entryDoorEnd=1299;
int exitDoorStart=1300,exitDoorEnd=2300;
long cntTotal=345;
long cntAlaram=1;
float cntTemp=95.10;
float cntMax=100.4;
int cntTempRound;
int cntEntryCount;
int range;
//-----------------------------------------------------------object creation

//Adafruit_MLX90614 mlx = Adafruit_MLX90614();    //thermal object creation
RTC_DS3231 rtc;    //rtc object creation 


int eeAddressAlaram=10;
int eeAddressEntryWithTempCheck=20;  //do entery  when temp safe
int cntEntryWithTempCheck;
int eeAddressEntryWithoutTempCheck=30;
int eeAddressExitWithoutTempCheck=40;
int cntEntryWithoutTempCheck;
int cntExitWithoutTempCheck;
int valueToEEPROM;

int max_limit=110 ; //prev value 75
int min_limit=30;  //prev value 30
//---------------------------------------pin declaration
 int TRIGGERPIN=33;
int ECHOPIN=31;
   int buzzerPin ;

 //  int buzzerPin = 45; // coommented  ******************************************  plz remove this comment
   int led1PinGreen = 39;      //soap out ,first relay start, dealy 5 sec       
   int led2PinRed = 37;      // wait for 20 sec, after 20s res will stop
   int but1=51;
   int but2;
   

   //---------------------------------------------------------------
long Duration = 0;

int motorDuration=0;
float feet;
int motorDurationFromEEPROM;
long Distance_mm;

String strDate ;
String strTime;

String dhm;
String datavalues;

int valueFromEEPROM ;

//------------------------------------milisecond declration
//---------------------------------------------------------------------------algo

//------------handle these three casese
// take temp (7s) ,then he he will go ------ no alraam           //case 1
//will not measure temo ,greater that 75 mm ot 2300 mm--------------give beep   //case 2 done
//take temp and again cross altrsonic (diif bet both record are of  min 7 second and max 11 second )then -----------------no beep  
    //once temp take then start mili second counting ,then if any entry detected (stop mili count)  within  10 second then dont give beep ,



//----- 
//----------------------------------------------------------------------------------
const unsigned long eventInterval = 7000;
unsigned long previousTime = 0;
unsigned long startTimeMilli=0;
unsigned long endTimeMilli=0;


//------------------------
void setup()
{

    Serial.begin(9600);
    tmrpcm.speakerPin=46;
    tmrpcm.setVolume(5);
//    mton.begin(9600);                  //mton 2 in setup
   if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:    //m6
    Serial.println("SD card module of display  not working properly");                                     //m7
   // return;   // don't do anything more if not    //m8
  }

  else                                                                                                           //m8
  {

     Serial.println("SD Card module of display is Ok.......................................................................");    //m9
     delay(1000);
     Serial.println("Playing testing sound .....");  //m10
      tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //m11
  }
     //---------------------------------------Thermal Setup
    
//      mlx.begin(); 
   
    //-------------------------------------- rtc setup


          if (! rtc.begin())
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
         //  rtc.adjust(DateTime(2020,11,28,5,51,00)); 
           
     //---------------------------------------Serial Setup
    
         //rtc.adjust(DateTime(2020,11,25, 1, 39, 00)); 
          
    
    
    if (!Serial) delay(5000);           //allow some time for Leonardo
    uint16_t ID = tft.readID(); //
   
    //-------------------------------------------------------------------------------unncessary code
    Serial.println(F("Diagnose whether this controller is supported"));
    Serial.println(F("There are FAQs in extras/mcufriend_how_to.txt"));
    Serial.println(F(""));
    Serial.print(F("tft.readID() finds: ID = 0x"));
    Serial.println(ID, HEX);
    Serial.println(F(""));
	Serial.print(F("MCUFRIEND_kbv version: "));
    Serial.print(version/100);
	Serial.print(F("."));
    Serial.print((version / 10) % 10);
	Serial.print(F("."));
    Serial.println(version % 10);
    Serial.println(F(""));
    if (ID == 0x0404) {
        Serial.println(F("Probably a write-only Mega2560 Shield"));
        Serial.println(F("#define USE_SPECIAL in mcufriend_shield.h"));
        Serial.println(F("#define appropriate SPECIAL in mcufriend_special.h"));
        Serial.println(F("e.g. USE_MEGA_16BIT_SHIELD"));
        Serial.println(F("e.g. USE_MEGA_8BIT_SHIELD"));
        Serial.println(F("Hint.  A Mega2560 Shield has a 18x2 male header"));
        Serial.println(F("Often a row of resistor-packs near the 18x2"));
        Serial.println(F("RP1-RP7 implies 16-bit but it might be 8-bit"));
        Serial.println(F("RP1-RP4 or RP1-RP5 can only be 8-bit"));
    }
    if (ID == 0xD3D3) {
        uint16_t guess_ID = 0x9481; // write-only shield
        Serial.println(F("Probably a write-only Mega2560 Shield"));
        Serial.print(F("Try to force ID = 0x"));
        Serial.println(guess_ID, HEX);
        tft.begin(guess_ID);
    }
    else tft.begin(ID);
    Serial.println(F(""));
    if (tft.width() == 0) {
        Serial.println(F("This ID is not supported"));
        Serial.println(F("look up ID in extras/mcufriend_how_to.txt"));
        Serial.println(F("you may need to edit MCUFRIEND_kbv.cpp"));
        Serial.println(F("to enable support for this ID"));
        Serial.println(F("e.g. #define SUPPORT_8347D"));
        Serial.println(F(""));
        Serial.println(F("New controllers appear on Ebay often"));
        Serial.println(F("If your ID is not supported"));
        Serial.println(F("run LCD_ID_readreg.ino from examples/"));
        Serial.println(F("Copy-Paste the output from the Serial Terminal"));
        Serial.println(F("to a message in Displays topic on Arduino Forum"));
        Serial.println(F("or to Issues on GitHub"));
        Serial.println(F(""));
        Serial.println(F("Note that OPEN-SMART boards have diff pinout"));
        Serial.println(F("Edit the pin defines in LCD_ID_readreg to match"));
        Serial.println(F("Edit mcufiend_shield.h for USE_SPECIAL"));
        Serial.println(F("Edit mcufiend_special.h for USE_OPENSMART_SHIELD_PINOUT"));
       while (1);    //just die
    } else {
        Serial.print(F("PORTRAIT is "));
        Serial.print(tft.width());
        Serial.print(F(" x "));
        Serial.println(tft.height());
        Serial.println(F(""));
        Serial.println(F("Run the examples/graphictest_kbv sketch"));
        Serial.println(F("All colours, text, directions, rotations, scrolls"));
        Serial.println(F("should work.  If there is a problem,  make notes on paper"));
        Serial.println(F("Post accurate description of problem to Forum"));
        Serial.println(F("Or post a link to a video (or photos)"));
        Serial.println(F(""));
        Serial.println(F("I rely on good information from remote users"));
    }



    //----------------------------------------------------------------------------------------------------endof unncessary code
   //----------------------------------------------------------------altra setup

 
    //-------------------------------------------------eeprom setup



/*
    //-------------------------------------------------------uncoment if entrycount required 

    motorDuration= eRead(eeAddressAlaram);
if( motorDuration ==-1)
{
 EEPROM.put(eeAddressAlaram,0);  //by default setting
 motorDuration =0;
}    

 motorDuration= eRead(eeAddressAlaram);
//---------------------------------------------------------------------eeprom entry with temp check

 cntEntryWithTempCheck= eRead(eeAddressEntryWithTempCheck);
if( cntEntryWithTempCheck ==-1)
{
 EEPROM.put(eeAddressEntryWithTempCheck,0);  //by default setting
 cntEntryWithTempCheck =0;
}    

 cntEntryWithTempCheck= eRead(eeAddressEntryWithTempCheck);
//-----------------------------------------------------------------------------------------eeprom entry without temp check
 cntEntryWithoutTempCheck= eRead(eeAddressEntryWithoutTempCheck);
if( cntEntryWithoutTempCheck ==-1)
{
 EEPROM.put(eeAddressEntryWithoutTempCheck,0);  //by default setting
 cntEntryWithoutTempCheck =0;
}    

 cntEntryWithoutTempCheck= eRead(eeAddressEntryWithoutTempCheck);
 //--------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------uncoment above block if entry count required

/*
/*
  Serial.println(F("\n Reading mode value"));
   readModeFromMem=eRead(eeAddressAlaramMode);
   if(readModeFromMem ==-1)
    {
        EEPROM.put(eeAddressAlaramMode, 2);  //by default setting
        readModeFromMem=2;;
    } 
   else
   {
      prevState=readModeFromMem;
   }


   */
   


         

   
   //---------------------------------------------------------------------read 
   

     //cntAlaram=eRead(eeAddressAlaram);
     //cntAlaram=cntAlaram;



   //-------------------------------------static part

    funStatic();
    
         

   //-------------------------------end of static part
}

void loop()
{
   DateTime now = rtc.now();
   String strDate =   String(now.day(), DEC) + '/' + String(now.month(), DEC) + '/' + String(now.year(), DEC);

   Serial.println(String(now.month()));
   delay(1000);
 /*
    //---------------------------------------------------------------------------------------------------------------------------test block
   tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //m11
   delay(5000);
   Serial.println("playing ninetyfour wav file");
   //tmrpcm.play("ninetyfour.wav");
   delay(5000);
   //---------------------------------------------------------------------------------------------------------------
*/
  /*  
   ----------------------------------------test block 


   Serial.println("am calling to sendValues as testing purpose");
 sendValues(10.10,range,dhm); //void sendValues(float temp1,int range1,string dhm) //mton 3  ,give msg to dislpay

  
  
  //---------------------------------------------------------------------------------------------------------------------------test block
   tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset   //m11
   delay(5000);
   Serial.println("playing ninetyfour wav file");
   //tmrpcm.play("ninetyfour.wav");
   delay(5000);
   //---------------------------------------------------------------------------------------------------------------
  Serial.println("playing Ninety4 file");
  tmrpcm.play("Ninety4.wav");
  delay(3000);
   Serial.println("playing testPSD.wav file");
 // tmrpcm.play("testPSD.wav");
  delay(3000);
  
*/
   // funAltraSonic2();

   //-----------------------------read all value from eeprom


    //cntEntryWithTempCheck=eRead(eeAddressEntryWithTempCheck);-------------------------------------imp uncomeent if u want entry count
   // cntEntryWithoutTempCheck=eRead(eeAddressEntryWithoutTempCheck);


   funStatic();


    funAltraSonic();

//-------------------------------------------------------funStatic()     
   
    
   
  
    //-------------------------------------------------------------------------------
   //funDateTime();  
   
    
/*
   //--------------------------------------------divider temp
    tft.setCursor(10, 90);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
     tft.print("\n-------------------------");  //25

   //----------------------------------------------- 
    tft.setTextColor(YELLOW);
    tft.setTextSize(3);
   tft.setCursor(10, 135);
   tft.print("Total  ");
   tft.print(cntTotal);
   
   
   tft.setCursor(10, 175);
   tft.print("ALARAM ");
    tft.print(cntAlaram);

     tft.setCursor(10, 215);
   tft.print("MAX    ");
    tft.print(cntMax);
   //--------------------------------------------divider temp
    tft.setCursor(10, 255);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("\n-------------------------");  //25
   //---------------------------------------------------
    tft.setCursor(10, 320);
    tft.setTextColor(YELLOW);
    tft.setTextSize(4);
    tft.print("TEMP                   F\n");
    tft.setTextColor(WHITE);
    tft.setCursor(60, 360); //95.5
    tft.setTextSize(6);


    
   //---------------------------------------divider  r and d 
    
    tft.setCursor(10, 400);
    tft.setTextColor(WHITE);
     tft.setTextSize(2);
    tft.print("\n-------------------------");  //25

    //--------------------------------------------------------
    tft.setCursor(10, 440);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Developed By R and D Lab      Computer Department ");
    //---------------------------------------------------------------------
   // tft.print(height);
  /*  tft.setTextColor(WHITE);
    tft.setCursor(40, 130);
    tft.print(colorname[aspect]);
    tft.setCursor(40, 160);
    tft.setTextSize(1);
    //tft.print("MCUFRIEND_KBV_H_ = ");
    tft.print(version);
    if (++aspect > 3) aspect = 0;
    delay(2000);

    */

    
}

//----------------------------------------------------------------------  void funStatic Function
void funStatic()
{

  static uint8_t aspect = 0;
    
    const char *aspectname[] = {
         "PORTRAIT_REV",
    };
    const char *colorname[] = {  "" };
    uint16_t colormask[] = {RED};
    uint16_t ID = tft.readID(); //
    
    tft.setRotation(0); //*********
    int width = tft.width();
    int height = tft.height();
    tft.fillScreen(colormask[aspect]);
    tft.drawRect(0, 0, width, height, WHITE);
   // tft.drawRect(32, 32, width - 64, height - 64, WHITE);
       tft.drawRect(5, 5, width - 10, height - 10, WHITE); 
  
    //-------------------------------------------------------------------------------

    DateTime now = rtc.now();
String strDate =   String(now.day(), DEC) + '/' + String(now.month(), DEC) + '/' + String(now.year(), DEC);
String strTime=String(now.hour(), DEC) + ':' + String(now.minute(), DEC) + ':' + String(now.second(), DEC);


   tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.setCursor(10 ,40 );
   tft.print("TIME   ");
    tft.print(strTime);
    

  
     
    tft.setCursor(10 ,70 );
   tft.print("DATE   ");
    tft.print(strDate);

    
      //--------------------------------------------divider temp
    tft.setCursor(10, 90);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
     tft.print("\n-------------------------");  //25

   //----------------------------------------------- 
    tft.setTextColor(YELLOW);
    tft.setTextSize(2.5);

     tft.setCursor(10, 135);    //*** entry without chk
   //tft.print("Entry Without Check:");
   //tft.print(cntEntryWithoutTempCheck);
   
   tft.setCursor(10, 165);            //***entry with chk
   //tft.print("Entry With Check:  ");
   //tft.print(cntEntryWithTempCheck);
   
  
   tft.setCursor(10, 195);        //***alaram
   //tft.print("Alaram  :");
    //tft.print(cntAlaram);

     tft.setCursor(10, 320);
   tft.print("Air Qulity %  :");
    tft.print(cntMax);
   //--------------------------------------------divider temp
    tft.setCursor(10, 270);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("\n-------------------------");  //25
   //---------------------------------------------------
    tft.setCursor(10, 135);
    tft.setTextColor(YELLOW);
    tft.setTextSize(5);
    tft.print("TEMP              F\n");
    tft.setTextColor(WHITE);
    tft.setCursor(60, 360); //95.5
    tft.setTextSize(6);


    
   //---------------------------------------divider  r and d 
    
    tft.setCursor(10, 400);
    tft.setTextColor(WHITE);
     tft.setTextSize(2);
    tft.print("\n-------------------------");  //25

    //--------------------------------------------------------
    tft.setCursor(10, 440);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Developed By: Mrunal Wagh ");
    //---------------------------------------------------------------------
   // tft.print(height);
  /*  tft.setTextColor(WHITE);
    tft.setCursor(40, 130);
    tft.print(colorname[aspect]);
     tft.setCursor(40, 160);
    tft.setTextSize(1);
    //tft.print("MCUFRIEND_KBV_H_ = ");
    tft.print(version);
    if (++aspect > 3) aspect = 0;
    delay(2000);
   */
  
}


//------------------------------------------------------------altrasonice distance 

int funAltraSonic()
{


 digitalWrite(TRIGGERPIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGERPIN, HIGH); // Trigger pin to HIGH
delayMicroseconds(10); // 10us high
digitalWrite(TRIGGERPIN, LOW); // Trigger pin to HIGH

Duration = pulseIn(ECHOPIN,HIGH); // Waits for the echo pin to get high

long Distance_mm = Distance(Duration); // Use function to calculate the distance

Serial.print("Distance = "); // Output to serial
Serial.print(Distance_mm);
Serial.println(" mm");



   tft.setTextColor(YELLOW);
    tft.setTextSize(2.5);
    tft.setCursor(10 ,350);
    tft.print("Dist.   :");
   
    tft.setCursor(150 ,350);
    tft.print(Distance_mm);
delay(1000); // Wait to do next measurement



//----------------exit management                                     //** need to return two varialbe and need to check wheather it is entry or exit 
/*
 
 if(Distance_mm>=exitDoorStart and Distance_mm<=exitDoorEnd)
{
    //read entry count and update it 

     cntExitWithoutTempCheck=eRead(eeAddressExitWithoutTempCheck);
     cntExitWithoutTempCheck=cntEntryWithoutTempCheck+1;
     eWrite(cntExitWithoutTempCheck,eeAddressExitWithoutTempCheck);
     Serial.println("\n----Exit without check");
     return( cntExitWithoutTempCheck);

 
}

*/
if(Distance_mm==0.0)
{

   //lcd.setCursor(0,1);
   //lcd.print("AT DS:0.0");
   Serial.print("\ndistandace is 0 ");
   //delay(1000);
   //lcd.clear();
   //lcd.setCursor(0,1);
   return(0);
}

else if(Distance_mm<=max_limit && Distance_mm>min_limit)   //take temp
{

  //start temp delay counting 
  
  // lcd.print("Chk A S  con < 0.10");
   Serial.print("\n Distance is less than 30 to 50 mm ");
  //call to single mode /double mode

  

  //take remp reading 
 
  takeTemp();
   return(1);
}
else if(feet<0.0)  
{

  //lcd.setCursor(0,1);
 //  lcd.print("Negative");
   Serial.print("\n Distance is in negative \n ");
   delay(1000);
   //lcd.clear();
   //lcd.setCursor(0,1);
   return(0);
}
else
{

  return(0);
}

   
  
 


}  //-----------end of fun altra sonic

//--------------------------------------------------------------------------date time
void funDateTime()
{

DateTime now = rtc.now();
String strDate =   String(now.day(), DEC) + '/' + String(now.month(), DEC) + '/' + String(now.year(), DEC);
String strTime=String(now.hour(), DEC) + ':' + String(now.minute(), DEC) + ':' + String(now.second(), DEC);

dhm=strDate+" "+strTime;
Serial.println("date time as follow ----------------------------------------------------------------------------------");
Serial.println(dhm);
Serial.println("..... am printing date time ");
    tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.setCursor(80 ,40 );
     tft.print("TIME   ");
    tft.print(strTime);

   /* tft.setCursor(10 ,50 );
    tft.print("Distance   ");
    tft.print(Distance_mm);
 */
    
    
    tft.setCursor(80 ,70 );
     tft.print("DATE   ");
    tft.print(strDate);

//Serial.println(strDate);
//Serial.println(strTime);
//delay(1000);




}

//-------------------------------------------------------------------------- alaram
void funAlaram()
{
Serial.println("\n funAlaram under constrction");



 

   digitalWrite(buzzerPin,HIGH);
   digitalWrite(led2PinRed,HIGH);
  delay(3000);
   digitalWrite(led2PinRed,LOW);
  digitalWrite(buzzerPin,LOW);
  
 //------------------------------------write alaram count into eeprom
   //cntAlaram=eRead(eeAddressAlaram);  //uncomment if entry count required on display
  //cntAlaram=cntAlaram+1;//uncomment if entry count required on display
    //eWrite(cntAlaram,eeAddressAlaram);//uncomment if entry count required on display

    //-----------
  tft.setTextColor(YELLOW);
  tft.setTextSize(3);
   tft.setCursor(10, 175);
   tft.print("ALARAM ");
    tft.print(cntAlaram);
    cntAlaram=cntAlaram;

}

//--------------------------------------------------------------------------entry
void funEntry()
{

  Serial.println("\n funentry under constrction");


}
//--------------------------------------------------------------------------


int eRead(int address)
{
  EEPROM.get(address, valueFromEEPROM );
  Serial.println(F("Motor Duration from EEPROM"));
  Serial.println(valueFromEEPROM);

   
  return(valueFromEEPROM);
}

void  eWrite( int valueToEEPROM, int eeAddressEEPROM)
{
    EEPROM.put(eeAddressEEPROM, valueToEEPROM);
   
  
}

//---------------------------------------
void takeTemp()
{
//cntTemp= mlx.readObjectTempF();
Serial.println("______________________________________________________________");
Serial.println(cntTemp);
//formaula 
     
    if(cntTemp>=cntMax)
    {
       //-------------------------temp disply formating   if temp >104.5

        tft.setTextColor(WHITE);
        tft.setCursor(120, 190); //95.5
        tft.setTextSize(6);
        cntTempRound=round(cntTemp)+9;
        tft.print(cntTempRound);
        funPlayFile(cntTempRound);
       //------------------------end of temp display formating
       
       
      funAlaram();
    }
    else 
    {
      //funGiveBeep(500);
      
        tft.setTextColor(WHITE);
        tft.setCursor(120, 190); //95.5
        tft.setTextSize(6);
        
        //cntTempRound=round(cntTemp)+9.20; //**exact important as per calibration
        cntTempRound=round(cntTemp)+9;
        tft.print(cntTempRound);
        
       // digitalWrite(led1PinGreen,HIGH);
        //delay(2000);
        // digitalWrite(led1PinGreen,LOW);
        funPlayFile(cntTempRound);
       
       //****
        //show temp without round-------------------------------------$
        
          //tft.setCursor(180 ,255);
          //tft.setTextSize(2);
          //tft.print(cntTemp+9.20);
        //--------------------------------------------
       
        
       
            //  cntEntryWithTempCheck=eRead(eeAddressEntryWithTempCheck);  //uncomment if entry count required on display
            //  cntEntryWithTempCheck=cntEntryWithTempCheck+1;//uncomment if entry count required on display
            // eWrite(cntEntryWithTempCheck,eeAddressEntryWithTempCheck);//uncomment if entry count required on display
            //  cntEntryWithTempCheck=eRead(eeAddressEntryWithTempCheck);//uncomment if entry count required on display
       //return(cntEntryWithTempCheck);
    }


} //-end of function



//----------------------------


void   funAltraSonic2()
{
  //lcd.clear();
  //lcd.print(0, 0, "Distance in Feet"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGERPIN, LOW);
  
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration * 0.034) / 2;
  float feet = distance / 30.48;
  Serial.print(feet);
  Serial.println("feet");
 
 // lcd.print(7, 1, feet);
  //Blynk.run(); //***********

  delay(2000);



}

long Distance(long time)
{
// Calculates the Distance in mm
// ((time)*(Speed of sound))/ toward and backward of object) * 10

long DistanceCalc; // Calculation variable
DistanceCalc = ((time /2.9) / 2); // Actual calculation in mm
//DistanceCalc = time / 74 / 2; // Actual calculation in inches
return DistanceCalc; // return calculated value
}

//--------------------

void funUnnecessaryCode()
{



}

//---------------------------
void funGiveBeep(int varMiliSecond)
{
 digitalWrite(buzzerPin,HIGH);
 delay(varMiliSecond);
 digitalWrite(buzzerPin,LOW);

}

//----------------------------------beginof Makuna



//--------------------------------------------


void funPlayFile(int ch)
{

  Serial.println("am in funplayfunction ");

 switch(ch)
 {

  
  case 80: Serial.println("playing file 80");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("eighty.wav");
           delay(3000); 
           digitalWrite(led1PinGreen,LOW);
           break;
  case 81: Serial.println("playing file 81");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("eone.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           break;
  case 82: Serial.println("playing file 82");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("etwo.wav");
           digitalWrite(led1PinGreen,LOW);
           delay(3000);
           break;
  case 83: 
            Serial.println("playing file 83");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("ethree.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           break;
  case 84: Serial.println("playing file 84");
           tmrpcm.play("efour.wav");
           delay(3000);
           break;
  case 85: Serial.println("playing file 85");
           tmrpcm.play("efive.wav");
           delay(3000);
           break;
  case 86:  Serial.println("playing file 86");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("esix.wav");
           digitalWrite(led1PinGreen,LOW);
           delay(3000);
           break;
  case 87: Serial.println("playing file 87");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("eseven.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           break;
  case 88: Serial.println("playing file 88");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("eeight.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           break;
  case 89: Serial.println("playing file 89");
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("enine.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           
           break;
  case 90: Serial.println("playing file 90");
           
           digitalWrite(led1PinGreen,HIGH);
           tmrpcm.play("ninety.wav");
           delay(3000);
           digitalWrite(led1PinGreen,LOW);
           break;
  case 91:Serial.println("playing file 91");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("none.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
  case 92:Serial.println("playing file 92");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("ntwo.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
  case 93:Serial.println("playing file 93");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("nthree.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
  case 94:Serial.println("playing file 94");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("nfour.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
  case 95:Serial.println("playing file 95");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("nfive.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
 
  case 96: Serial.println("playing file 96");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("nsix.wav"); 
          delay(3000);
         digitalWrite(led1PinGreen,LOW);
          break;
  case 97: Serial.println("playing file 97");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("nseven.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,LOW);
          break;
  case 98:Serial.println("playing file 98");
          digitalWrite(led1PinGreen,HIGH);
          tmrpcm.play("neight.wav"); 
          delay(3000);
          digitalWrite(led1PinGreen,HIGH);
          break;
          digitalWrite(led1PinGreen,LOW);
  case 99:Serial.println("playing file 99");
          digitalWrite(led2PinRed,HIGH);
          tmrpcm.play("nnine.wav"); 
          delay(3000);
          digitalWrite(led2PinRed,LOW);
          break;
  case 100:Serial.println("playing file 100");
             digitalWrite(led2PinRed,HIGH);
           tmrpcm.play("h.wav");
           delay(3000);
             digitalWrite(led2PinRed,LOW);
           break;
  case 101: Serial.println("playing file 101");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hone.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 102 :Serial.println("playing file 102");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("htwo.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 103: Serial.println("playing file 103");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hthree.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 104: Serial.println("playing file 104");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hfour.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 105: Serial.println("playing file 105");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hfive.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 106: Serial.println("playing file 106"); 
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hsix.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 107: Serial.println("playing file 107");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hseven.wav");
              digitalWrite(led2PinRed,LOW);
            delay(3000);
            break;
  case 108: Serial.println("playing file 108");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("height.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;
  case 109: Serial.println("playing file 109");
              digitalWrite(led2PinRed,HIGH);
            tmrpcm.play("hnine.wav");
            delay(3000);
              digitalWrite(led2PinRed,LOW);
            break;


 
  default:Serial.println(" playing out of range file");
          tmrpcm.play("Veryhl.wav");
          delay(3000); 
 } //end of switch

 // call to send values bcz it will create delay
 range=1; //feth record from  smart card 
Serial.println("am calling to sendValues from switch loop");
 sendValues(float(ch),range,dhm); //void sendValues(float temp1,int range1,string dhm) //mton 3  ,give msg to dislpay


 
}//end of play mp3 fun

//---------------------------------------------------------------------------------------------------------------------------

void sendValues(float temp1,int range1,String dhm1)        //mton 4 block
{
   
Serial.println("\nvalues before uploading to gateway");     //---------production comment
Serial.println("\nTempraturevalue is:");
Serial.println(temp1);
Serial.println("\n Range value is:");
Serial.println(range1);
Serial.println("\n Time Stamp is");
Serial.println(dhm1);
Serial.println("\n Now sending");             //---------production comment

//datavalues =String(String(temp1)+String(",")+String(range1)+String(","));
datavalues =String(String(temp1)+String(",")+String(range1)+String(",")+String(dhm1)+String(","));
//splitStr(datavalues);

Serial.println("Print data Values array ");   //---------production comment
Serial.println(datavalues);                   //---------production comment
//mton.println(datavalues);
Serial.println("Data sent to node mcu  sucessfully");   //---------production comment

    tft.setTextColor(YELLOW);
    tft.setTextSize(2.5);
    tft.setCursor(10 ,380);
    tft.print("Data sent to Cloud Sucess");
  
  }
