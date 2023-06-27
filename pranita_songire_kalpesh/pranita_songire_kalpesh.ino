#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Wire.h>// i2c LCD
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
#include <Servo.h>
SoftwareSerial mySerial(10,11);//tx rx

Servo myservo;
String pwd;
String str;
int str_len; 
String Otp;
int otp_flag=0;
String otpp = "";
String numbers[6]={"321153", "212135", "999956", "543646", "995956", "543446"};
//LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
 
#define Password_Lenght 7 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
int O_TP_FLAG=0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
   {'1','4','7','*'},
   {'2','5','8','0'},
   {'3','6','9','#'},
   {'A','B','C','D'}
   };
bool door = true;

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad


Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad


//---------------------------------------------------------------------------------void setup------------------------------------------------------------------------
   void setup()
    {
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
    mySerial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.clear();

  myservo.attach(9);
  ServoClose();
  
  lcd.begin(16, 2);
  lcd.print("Smart Vehicle ");
  lcd.setCursor(0, 1);
  lcd.print("--Locking et--");
  delay(3000);
  lcd.clear();
  }
   
//------------------------------------------------------------------------------------main program---------------------------------------------------------------------     
    
 
     void loop()    
     {
    
     
     if (O_TP_FLAG == 0)
     {
      otp();
      SendMessage();
      O_TP_FLAG=1;
     }
     if (door == 0)
     {
     customKey = customKeypad.getKey();

     if (customKey == '#')

      {
      lcd.clear();
      ServoClose();
      digitalWrite(13, LOW);
      digitalWrite(A0, LOW);
      lcd.print("  Vehicle Off");
      delay(3000);
      door = 1;
      O_TP_FLAG=0;
      }
    
      }

     else Open();
     }
  //-----------------------------------------------------------------------------------------void OTP------------------------------------------------------------------
   
      void otp()
      {
      otpp = numbers [random(0, 6)] ;
      Otp=otpp;
      Serial.println(otpp+"\n");
      lcd.clear();
      //lcd.print(Otp);
      
      lcd.setCursor(0, 1);
      lcd.print("OTP send To Mo.");
      delay(3000);
      lcd.clear();
      delay(5000);
     
  //-------------------------------------------------------------------void clear data--------------------------------------------------------------------------
     }
     void clearData()
     {
     while (data_count != 0)
     {    // This can be used for any array size,
     Data[data_count--] = 0; //clear array for new data
     }
     return;
     }
   
   //------------------------------------------------------------------------servo-------------------------------------------------------------------------------

      void ServoOpen()
      {
      for (pos = 180; pos >= 0; pos -= 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      }
      }

      void ServoClose()
      {
        digitalWrite(13, LOW);
        digitalWrite(A0, LOW);
      for (pos = 0; pos <= 180; pos += 5) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      }
      }

   //--------------------------------------------------------------------------------------void open--------------------------------------------------------------------
   
     void Open()
     {
     lcd.setCursor(0, 0);
     lcd.print(" Enter Password");
  
     customKey = customKeypad.getKey();
     if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
     {
     Data[data_count] = customKey; // store char into data array
     lcd.setCursor(data_count, 1); // move cursor to show each new char
     lcd.print(Data[data_count]); // print char at said cursor
     data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
     }

      if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
      {
      str = Otp;
      str_len = str.length() + 1; 
      char char_array[str_len];
      str.toCharArray(char_array, str_len);
      
      if (!strcmp(Data, char_array)) // equal to (strcmp(Data, Master) == 0)
      {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Face Detection");
      delay(6000);
      check();
      //ServoOpen();
      //lcd.print("  Vehicle ON");
      door = 0;
      }
      else
      {
      lcd.clear();
      lcd.print("  Wrong Password");
      delay(1000);
      door = 1;
      }
      clearData();
      }
      }
//-------------------------------------------------------------------------------------------send msg---------------------------------------------------------------------
      void SendMessage()
      {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+918766403908\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.println(Otp);// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
      }
      
//-----------------------------------------------------------------------------------motor----------------------------------------------------------------------------
     
     void check() 
     {
      lcd.clear();
      lcd.print("  check loop");
      delay(1000);
      lcd.clear();
      delay(4000);
     int sensorVal = digitalRead(12);
     Serial.println(sensorVal);

     if (sensorVal == HIGH)
     {
     digitalWrite(13, LOW);
     digitalWrite(A0, LOW);
     ServoClose();
     lcd.print("  Vehicle off");
     
     }
     else 
     {
     digitalWrite(13, HIGH);
     digitalWrite(A0, HIGH);
     ServoOpen();
     lcd.print("  Vehicle ON");
     }
     }
      
   
  //-----------------------------------------------------------------------------------END--------------------------------------------------------------------------------
