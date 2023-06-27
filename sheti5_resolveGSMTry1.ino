
#include<LiquidCrystal.h>    
#include <SoftwareSerial.h>
//SoftwareSerial msgSerial(52,53);
SoftwareSerial msgSerial(53,52); //tx,rx
SoftwareSerial mton(10,11);
const int sensorMin = 0; 
const int sensorMax = 1024; 
#include <SPI.h> 
int range;
const int soilPinAnalog=A8; // /* Soil moisture sensor O/P pin */// initialize sensor pin
const int rainPinAnalog=A15;
const int soilPinDigital=22;  ///* Soil moisture sensor O/P pin */// initialize sensor pin
String datavalues;

float t, h;

//------------
float moisture_percentage;
  int sensor_analog;
  
int buzzerPin = 40;  

//----------------------------------------mrunal sheti pin declarations
//----------------------------------Display
LiquidCrystal lcd(3,4,5,6,7,8);
//--------------------------Float
int float1=47;
int float2=49;
int float3 =51;
//------------------------------- motor lED
int motorLEDYellow=27;
int motorLEDRED=29;
//----------------------------------------water level led
int waterLEDYellow=48;  //33-48  //made it off
int waterLEDRed=31;
//-------------------------------------power led 1
int pinPowerLED=43;
int butRetValueFromMem=37;
//---------------------------------------------------------------------------------

   String strdd="";
   String strmonth="";
   String stryy="";
   String  dhm ="";
   String strmm="";
   String strss="";
   String strhh="";
//----------------
void setup() {

    Serial.println("\n\n");
   digitalWrite(pinPowerLED,HIGH);
  Serial.begin(9600); /* Define baud rate for serial communication */
  mton.begin(9600);
pinMode(soilPinAnalog, INPUT); 
pinMode(soilPinDigital, INPUT); 
pinMode(pinPowerLED,OUTPUT);

 pinMode(motorLEDYellow, OUTPUT);
   pinMode(motorLEDRED, OUTPUT);
    pinMode(waterLEDYellow, OUTPUT);
     pinMode(waterLEDRed, OUTPUT);

funPartyWelcome("KissanFarma Agriculture Pvt Ltd.");
delay(1000);
//-------------------------------------------------------------------------------------------------------------------------------------
    lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9

    //clear the screen
    lcd.print("   Welcome   ");  //displaying the message on LCD
    delay(1000);
    
     lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9
     msgSerial.begin(9600);
    //clear the screen
    lcd.print("Kissan Farma");  //displaying the message on LCD
     lcd.setCursor(0,1);       // set the cursor at position (C1,R0)  //display 8
     lcd.print("Agri. Pvt Ltd");  //displaying the message on LCD
  
    Serial.println("Kissan Farma Agri. Pvt Ltd");
    delay(500);
   //  digitalWrite(waterLEDYellow,HIGH);
}

//-------------------------------------------------------------------------------------------------

void loop()
{ 
  
    //funSirren();
    
    // gsmTest();
     sensor_analog = analogRead(soilPinAnalog);
     moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
     String moisture_percentage_str=String(moisture_percentage) +"%";
     showOnLCDGeneral("moisture_percentage",moisture_percentage_str);
     
       //testCountDown(20000/1000);
 
      range=chkRainLevel();
      Serial.println("Range:");
        Serial.println(range);
 
    delay(1000);

  if(range==0 )  //0 rainy(heavy(,1 warning(cloudy) ,2 not raining 
  {

    //print on lcd
 
    showOnLCD3(t,"Heavy Rain","Downey");
    SendMessageMotor("Heavy Rain");  //void SendMessage(float temp,String strRainCondion,String Dis)
    showOnLCDGeneral("Text Msg","sent");
    
    Serial.print("Message Heavy Rain Downey done");
    delay(1000);
  }

readFloats();
   

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

int sensorReading = analogRead(rainPinAnalog);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

   return(range);
  delay(1000); 

}

//------------------------
  

void SendMessage()
{
  msgSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  msgSerial.println("AT+CMGS=\"+919921287780\"\r"); // Replace x with mobile number
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
  String Str="Temp 30.30  Rain Condition: Cloudy Disease :Powedery";
  msgSerial.println( Str);// The SMS text you want to send
  delay(100);
  msgSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}



void funPartyWelcome(String partyName)
{
    lcd.clear();
    lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  
    lcd.print("Welcome      To");
    lcd.setCursor(0,1);       // set the cursor at position (C1,R0)  
    lcd.print(partyName);
    delay(500); //1 sec
    lcd.clear();
}
    void readFloats()
{
      int f3=digitalRead(float1);
      int f2=digitalRead(float2);
      int f1=digitalRead(float3);


 
//--------------------------------------------------------------F1
    if(f1==0)
    {

        // motor led will be red 
        // void funLED(int ledPin1 ,int status1,int delay1);
           digitalWrite(motorLEDRED,HIGH);
           digitalWrite(motorLEDYellow,LOW);
      
    //do gsm call  
        DialCall();
        showOnLCDGeneral("Doing call on","9921287780");
        showOnLCDGeneral("First Checkpoint","Mtr not in Water");
    }
   else if(f1==1)
   {

     //motor yellow led will be on
       digitalWrite(motorLEDYellow,HIGH);
       digitalWrite(motorLEDRED,LOW);
     //show msg to display -Motor is in water
 
     showOnLCDGeneral("First Checkpoint","Motor in Water");
   }
//----------------------------------------------------------------------F2
  if(f2==0)
    {

    //do gsm msg  
  
     SendMessageMotor("Mtr not in Water");  
     showOnLCDGeneral("2 Chkpt Msg Sent","Mtr Not In Wt");
 

    }
   else if(f2==1)
   {
    // no any action 
     showOnLCDGeneral("Second Checkpoint","Mtr in Water");
 
   }
 ;
 
   //----------------------------------------------------- F3
     if(f3==0)
    {
           //showOnLCDGeneral("f3==0 in","above waterLEDRED");
  
    //motor led will be red 
   // void funLED(int ledPin1 ,int status1,int delay1);
    // digitalWrite(waterLEDYellow,LOW);
   //  digitalWrite(waterLEDRed,HIGH);

      //showOnLCDGeneral("test f3==0 in","below waterLEDYellow");
      
    //dont do gsm call                                                          ???
   showOnLCDGeneral("Third Checkpoint","Water Level Low");
    }
   else if(f3==1)
   {
// showOnLCDGeneral("f3==1 in","above waterLEDYellow");
     
     //motor yellow led will be on
    
      //showOnLCDGeneral("f3==1 in below ","waterLED Yellow");
    //  digitalWrite(waterLEDRed,LOW);
      //delay(1000);
    // digitalWrite(waterLEDYellow,HIGH);
// showOnLCDGeneral("test f3==1 in","below water LED RED");
 
     showOnLCDGeneral("Third Checkpoint","Water level HIGH");
   }
 
}


//------------ --------------------------------------------------------------


//void funLED(int ledPin1 ,int delay1)
//{
  // digitalWrite(ledPin1,HIGH);
   //elay(delay1);
   //digitalWrite(ledPin1,LOW);
//}

void DialCall()
{
    Serial.println("am doing call from dial call ");
    msgSerial.println("ATD+919921287780;");        // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  // msgSerial.println("ATD+917391853796;");        // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  
    delay(20000);
}

void SendMessageMotor(String msg)
{
  msgSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  msgSerial.println("AT+CMGS=\"+919921287780\"\r"); // Replace x with mobile number   anant 
   // msgSerial.println("AT+CMGS=\"+917391853796\"\r"); // Replace x with mobile number   anant 
 
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
  // msgSerial.println("I am SMS from GSM Module");// The SMS text you want to send
  String str=msg;
  msgSerial.println(str);// The SMS text you want to send
  delay(100);
  msgSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void gsmTest()
{

  Serial.println("Test : am in gsm test function ");

   msgSerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();
    delay(1000);
  // msgSerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best  updateSerial();
   //msgSerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  //updateSerial();
   //msgSerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
}

void updateSerial()
{
 // Serial.println("Test : am in update serial ");
  delay(500);
 /*  while (Serial.available()) 
   {
     msgSerial.write(Serial.read());//Forward what Serial received to Software Serial Port
   }
   */
  while(msgSerial.available()>0) 
  {    
  //  Serial.println("Test : got data on msgSeriall ");
     String str=String(msgSerial.read());
     Serial.println("extracted complete string");
     Serial.write(msgSerial.read());
     String workingString = str.substring(0,4);
    Serial.println("extracted characters o to 4");
    Serial.println(workingString);
 if(workingString=="RING")
 {

    Serial.println("String RING detected");
 }
 else
 {

 Serial.println("String RING not detected");
  
 }
  }//wnd of while

  
 } //end of fun

//------------------------check call received routine 

void checkRingWord(String msg)
{



  //extract ring word and moibile number
  //if ring from specified mobile number then activate siren pin 


}

void funSirren()
{

             for(int i=0;i<10;i++)
              {
                digitalWrite(buzzerPin,HIGH);
                Serial.println("Sirron on");
                delay(2000);
                digitalWrite(buzzerPin,LOW);
                 Serial.println("Sirron off");
           
           
               }
}
