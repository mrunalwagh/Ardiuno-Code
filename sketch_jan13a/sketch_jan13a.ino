
#include <LiquidCrystal.h>
   LiquidCrystal lcd(11, 12, 2, 3, 4, 5);
  #define buzzerPin 8
   #define scoilPin 6
   #define gasPin A0
   void setup() {
   Serial.begin(9600);
   lcd.begin(16, 2); 
   pinMode(buzzerPin,OUTPUT);
   pinMode(scoilPin,OUTPUT);
   lcd.setCursor(0, 0);
    lcd.print("Calibrating");
   for(int i = 0; i <10; i++){
      if (i==4)
      {
         lcd.setCursor(0, 1);
         lcd.print(".");
        }
       else  lcd.print(".");
      delay(500);
      }
    lcd.setCursor(5, 1);
    lcd.print("done");
    delay(1000);
    lcd.clear(); 
    lcd.setCursor(1, 0);
    lcd.print("SENSOR ACTIVE");
    delay(1500);
    lcd.clear();
}

void loop() 

  {
  int gasSensor = analogRead(gasPin);
   if (gasSensor > 670){
     digitalWrite(buzzerPin,LOW);
     digitalWrite(scoilPin,LOW);
     lcd.setCursor(0, 0);
     lcd.print("Value : ");
     lcd.print(gasSensor);
     Serial.print(gasSensor);
     Serial.print("\t");
     lcd.setCursor(0, 1);
     Serial.println("LPG Gas Detected");   
     lcd.print("LPG Gas Detected");  
     delay(300); 
     lcd.clear();
      }
    else 
        {
     digitalWrite(buzzerPin,HIGH);
     digitalWrite(scoilPin,HIGH);
     lcd.setCursor(0, 0);
     lcd.print("Value : ");
     lcd.print(gasSensor);
     Serial.print(gasSensor);
     Serial.print("\t");
     lcd.setCursor(0, 1);
     Serial.println("You Are Safe"); 
     lcd.print("You Are Safe");   
     delay(300);
   }
  
  }
