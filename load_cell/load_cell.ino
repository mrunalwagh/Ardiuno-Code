 //this project Code Run..... When Hardware Is Cannected
//RSET = V1  BLYNK
//SOIL = V5   BLYNK
//WEIGHT = V3  BLYNK


#include <ESP8266WiFi.h>
#include "HX711.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BLYNK_PRINT Serial
 
const char *ssid = "hac"; // replace with your wifi ssid and wpa2 key
const char *pass = "hac123456";
char auth[] = "YiUN8hAkxNK5Fbx7vNjHqSn7aZURmCwN";    // You should get Auth Token in the Blynk App.
 
WiFiClient client;
 
HX711 scale(D5, D6);//D5=DT, D4=6SCK
 
int rbutton = D1; // this button will be used to reset the scale to 0. (RSET = V1)
float weight;
float calibration_factor = -101525; // for me this vlaue works just perfect 419640

int analogPin = D0;
int moisture;
int percentage;
int map_low = 686;//.................orignal 686
int map_high = 686;

void setup() 
{
  Serial.begin(115200);
  pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Blynk.begin(auth, ssid, pass);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.setCursor(6,0);
  lcd.print("IOT");
  lcd.setCursor(1,1);
  lcd.print("Weighing Scale");
  delay(3000);
  lcd.clear();
 
  lcd.print("Connecting Wifi");
  
  WiFi.begin(ssid, pass);
  {
  delay(1000);
  Serial.print(".");
  lcd.clear();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.print("WiFi connected");
  delay(2000);
}
 
void loop() 
 
{
 
  Blynk.run();
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(5); 
  Blynk.virtualWrite(V3, weight);
  delay(2000);
 
  lcd.setCursor(0, 0);
  lcd.print("Measured Weight");
  lcd.setCursor(0, 1);
  lcd.print(weight);
  lcd.print(" KG  ");
  
  delay(2000);
  lcd.clear();
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");
  Serial.println();
  
   if ( digitalRead(rbutton) == LOW)
{
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
}

  moisture = analogRead(analogPin);
  Serial.print("Raw: ");
  Serial.print(moisture);
  percentage = map(moisture, map_low, map_high, 0, 100);
  Serial.print(" | Percentage: ");
  Serial.print(percentage);
  Serial.println("%");
  delay(1000);
  
  Blynk.virtualWrite(V5, percentage);
  
  Blynk.virtualWrite(V1, rbutton);
  delay(1000);
 }
