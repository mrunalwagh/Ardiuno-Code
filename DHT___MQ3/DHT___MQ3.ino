#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] = "QSCHWaxIUMI3rAvMAXXvbOuddfWhEydm"; //Enter the Auth code which was send by Blink

char ssid[] = "hack";  //Enter your WIFI Name
char pass[] = "Easy@2021";  //Enter your WIFI Password
LiquidCrystal_I2C lcd(0x27,20,4);
#define DHTPIN 4         


#define DHTTYPE DHT11     
#define buzzerPin 16 

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int gasSensor;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("℃");
  
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print("%");

  gasSensor=analogRead(A0);
  Serial.println(gasSensor);
  
  if(gasSensor>400)
  {
    digitalWrite(13,LOW);
    digitalWrite(14,HIGH); 
     lcd.setCursor(0, 2);
     lcd.print("Value: ");
     lcd.print(gasSensor);
     lcd.setCursor(0, 3);
     lcd.print("Gas detected");
     tone(buzzerPin,800,40); 
    
  }
  
  if(gasSensor<400)
  {
      digitalWrite(13,HIGH);
      digitalWrite(14,LOW);
      lcd.setCursor(0, 2);
      lcd.print("Value: ");
      lcd.print(gasSensor);
      lcd.setCursor(0, 3);
      lcd.print("---No gas---");
      noTone(buzzerPin);
      
  }

  Blynk.virtualWrite(V1, gasSensor);
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
  
}

void setup()
{
  Serial.begin(115200); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  
  timer.setInterval(1000L, sendSensor);
  
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

 
  
}
