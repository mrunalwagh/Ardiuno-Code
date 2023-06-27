   #include <LiquidCrystal.h>
   #include <SoftwareSerial.h>
   
   LiquidCrystal lcd(7,6,5,4,3,2);  
   int arrivingdatabyte;  
   void setup( )  
   {  
  Serial.begin(9600);  
   }  
void loop( )  
{  
if(Serial.available( ) > 0)  
{  
arrivingdatabyte = Serial.read( );  // It will read the incoming or arriving data byte  
Serial.print("data byte received:");  
Serial.println(arrivingdatabyte); 
lcd.setCursor(0, 0);
     lcd.print("From PC: ");
     lcd.print(arrivingdatabyte);
    
}  
}  
