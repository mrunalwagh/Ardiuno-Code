#include <Servo.h>
Servo myservo1;
Servo myservo2;
int pos = 0;
#include<LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 11);
int timer1;
int timer2;
float Time;
int flag1 = 0;
int flag2 = 0;
float distance = 5.0;
float speed;
int ir_s1 = 9 ;
int ir_s2 = 8;
int buzzer = 10;
int red_led=7;
int led_green=6;
void setup()
{
myservo1.attach(12);
myservo2.attach(13);
pinMode(ir_s1, INPUT);
pinMode(ir_s2, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(red_led,OUTPUT);
pinMode(led_green,OUTPUT);
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" WELCOME ");
delay(2000);
lcd.clear();
}
void loop()
{
if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
if(timer1 > timer2){Time = timer1 - timer2;}
else if(timer2 > timer1){Time = timer2 - timer1;} Time=Time/1000;//convert millisecond to second
speed=(distance/Time);//v=d/t
speed=speed*3600;//multiply by seconds per hr
speed=speed/1000;//division by meters per Km
}

if(speed==0){
lcd.setCursor(0, 1);
if(flag1==0 && flag2==0){lcd.print("No car detected");}
else{lcd.print("Searching... ");}
}
else{ lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Speed:");
lcd.print(speed,1);
lcd.print("Km/Hr ");
lcd.setCursor(0, 1);
if(speed > 50){lcd.print(" Over Speeding ");
digitalWrite(buzzer, HIGH);
digitalWrite(red_led, HIGH);

delay(3000);
myservo1.write(180); 
myservo2.write(180);
delay(15);
delay(3000);
myservo1.write(5);
delay(15); 
myservo2.write(5);
delay(15);

digitalWrite(buzzer, LOW);
digitalWrite(red_led, LOW);
}
else{lcd.print(" Normal Speed ");
}
delay(3000);
digitalWrite(led_green, HIGH);
delay(3000);
digitalWrite(led_green, LOW);
speed = 0;
flag1 = 0;
flag2 = 0;
}
}
