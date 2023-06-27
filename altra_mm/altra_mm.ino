const int trigger = 12; //Trig pin
const int echo = 13; //Echo pin
long Duration = 0;


#include <LiquidCrystal.h>

LiquidCrystal lcd(3,4,5,6,7,8);


float time=0,filledDistance=0;
float totalDistance=44;
float finalDistance;
void setup(){

  lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
    lcd.setCursor(0,0);       // set the cursor at position (C1,R0)  //display 8

    //--------------------------------------------------------LCD module setup 
      // set up the LCD's number of columns and rows:
           
            delay(1000);
           Serial.println("LCD module is Ok...."); 
           lcd.print("initialising......");
            delay(2000);
pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
Serial.begin(9600); // Serial Output
}

void loop(){



}



void measureFilledDistance()
{
   lcd.clear();        // initialize LCD of size 16/2 (2 rows, 16 col) //display 7
}
