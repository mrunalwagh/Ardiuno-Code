
 #include<LiquidCrystal.h>    //display 1

#include <SoftwareSerial.h>
//SoftwareSerial mySerial(52,53);
SoftwareSerial mySerial(53,52); //tx,rx


//--------------

#include "DHT.h"

#define DHTPIN 41
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
const int soilPinAnalog = A5;  /* Soil moisture sensor O/P pin */// initialize sensor pin
const int soilPinDigital = 40;  /* Soil moisture sensor O/P pin */// initialize sensor pin


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

LiquidCrystal lcd(4,3,5,6,7,8);
//LiquidCrystal lcd(8,7,6,5,3,4);
//LiquidCrystal lcd(8,7,6,5,4,3);
//LiquidCrystal lcd(rs,en,d4,d5,d6,d7);   //display 7// configure the pin RS,enable,D4,D5,D6,D7  resp.  //original
int buzzerPin = 40;  
int pinPowerLED=43;


//----------------
void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  
pinMode(soilPinAnalog, INPUT); 
pinMode(soilPinDigital, INPUT); 
pinMode(pinPowerLED,OUTPUT);
pinMode(DHTPIN, INPUT); 


dht.begin();
//-----------------------
    lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
    lcd.clear();       ////display 9

    //clear the screen
    lcd.print("Welcome Grapes IoT");  //displaying the message on LCD
   mySerial.begin(9600);
}

void loop() {

delay(2000);
   // delay(dht.getMinimumSamplingPeriod());

 h  = dht.readHumidity();
  t= dht.readTemperature();
   if (isnan(h) || isnan(t) ) {    //|| isnan(f)
    Serial.println(F("Failed to read from DHT sensor!"));
   }               
      Serial.print("Temperature=");
      Serial.println(t,1);                                  
      Serial.print("Humidity=");
      Serial.println(h,1);                                
 /* Serial.println(dht.toFahrenheit(temperature), 1);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
 Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
 
 Serial.print(dht.getStatusString())
 */
    sensor_analog = analogRead(soilPinAnalog);
    moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
    Serial.print("Moisture Percentage = ");
    Serial.print(moisture_percentage);
    Serial.print("%\n\n");
    //--------------------------------------------------------
     lcd.clear();       ////display 9
     lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
     
     lcd.print("Temp:");  //displaying the message on LCD
     lcd.print(t);  //displaying the message on LCD
      lcd.print("Hum.:");  //displaying the message on LCD
     lcd.print(h);  //displaying the message on LCD

      lcd.clear();       ////display 9
     lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print("Moisture:");  //displaying the message on LCD
     lcd.print(moisture_percentage);  //displaying the message on LCD
    delay(2000);

   digitalWrite(pinPowerLED,HIGH);
   delay(100);
   digitalWrite(pinPowerLED,LOW);\
   delay(800);
   Serial.print("Message send");
   SendMessage();
   Serial.println();
   

}


//-----------------------------gsm code

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  //mySerial.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number
  mySerial.println("AT+CMGS=\"+917387335739\"\r"); // Replace x with mobile number
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void showOnLCD(String title,String msg)
{
     lcd.clear();       ////display 9
     lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  //display 8
     //clear the screen
     lcd.print(title);  //displaying the message on LCD
     lcd.print(msg);  //displaying the message on LCD
     delay(1000);
}
