#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int sensor_pin = A0; 
int output_value ;
int relayPin = 4;

void setup(){
  lcd.init();
  lcd.backlight();
  pinMode(sensor_pin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop(){
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,10,0,100);
  lcd.setCursor(0,0);
  lcd.print("Mositure: ");
  lcd.print(output_value);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  if(output_value>0){
   
  lcd.print("Motor ON");
  digitalWrite(relayPin,HIGH);
  delay(5000);
  lcd.clear();
  digitalWrite(relayPin,LOW);
  }
  
 else
 {
  digitalWrite(relayPin,LOW);
  lcd.setCursor(0,1);
  lcd.print("Motor OFF");
  lcd.clear();       
 }
  delay(2500);
  
}
