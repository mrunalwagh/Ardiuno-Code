#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BLYNK_PRINT Serial
 #include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = "PuOLGObhpzHxpvOVK35bglASb6A0u-vo";//Enter your Auth token
char ssid[] = "hack";//Enter your WIFI name
char pass[] = "Easy@2021";//Enter your WIFI password
 
BlynkTimer timer;
bool pinValue = 0;
bool pinValue1 = 0;
 
#define trig D4
#define echo D3
#define relay D0
#define relay1 D5
#define relay3 D1
 
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, Wlevel);
  digitalWrite(relay, HIGH);
  
}
 
BLYNK_WRITE(V0)
{
  pinValue = param.asInt();
}
BLYNK_WRITE(V2)
{
  pinValue1 = param.asInt();
}
 
void loop() {
  Blynk.run();
  timer.run();
}
 
void Wlevel() {
  if (pinValue == 1) {
    digitalWrite(relay, HIGH);
    
  } else if (pinValue == 0) {
    digitalWrite(relay, LOW); 
  }
  if (pinValue1 == 1) {
    digitalWrite(relay1, HIGH);
  } else if (pinValue1 == 0) {
    digitalWrite(relay1, LOW); 
  }

 
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;

  if(cm >= 150)
    digitalWrite(relay3, LOW);  //relay3 on
  else
    digitalWrite(relay3, HIGH);  //relay3 off 

 
  Blynk.virtualWrite(V1, cm);
  Serial.println(cm);
 
}
