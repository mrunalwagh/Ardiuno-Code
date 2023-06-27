

   #include <LiquidCrystal.h>
   #include <Servo.h>
   const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;    //7,6,5,4,3,2
   LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
   Servo myservo;
   int pos = 0;
   void setup()
   {
   Serial.begin(9600);
   pinMode(13,OUTPUT);
   pinMode(12,OUTPUT);
   pinMode(11,OUTPUT);
   lcd.begin(16,2);
   lcd.setCursor(0,0);
   lcd.print("      ANPR");
   lcd.setCursor(0,1);
   lcd.print("  Using Python");
   myservo.attach(9);
   ServoClose();
   delay(20);
   
   }

   void loop()
   {

   if(Serial.available())
   {
   switch(Serial.read())
   {
   case'1':
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("Authorized Car");
   
   digitalWrite(12,HIGH);
   digitalWrite(11,HIGH);
   delay(5000);
   digitalWrite(12,LOW);
   digitalWrite(11,LOW);
   lcd.clear();
   lcd.print("Gate Open");
   ServoOpen();
   delay(7000);
   lcd.clear();
   lcd.print("Gate Closed");
   delay(2000);
   ServoClose();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("      ANPR");
   lcd.setCursor(0,1);
   lcd.print("  Using Python");
   
   break;

    
   case'0':
   lcd.setCursor(0,1);
   lcd.clear();
   lcd.print("UnAuthorized Car");
   digitalWrite(13,HIGH);
   digitalWrite(11,HIGH);
   delay(5000);
   digitalWrite(13,LOW);
   digitalWrite(11,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("      ANPR");
   lcd.setCursor(0,1);
   lcd.print("  Using Python");
   break;
 
   }
   }
   }
  //-----------------------------------------------------------------------------------------------------------------------------------------------

      void ServoOpen()
      {
      for (pos = 90; pos >= 0; pos -= 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15ms for the servo to reach the position
      }
      }

      void ServoClose()
      {
        
      for (pos = 0; pos <= 90; pos += 5) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15ms for the servo to reach the position
      }
      }


   
