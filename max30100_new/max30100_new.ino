#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal.h>
 
#define REPORTING_PERIOD_MS     1000
#define rs 2 
#define en 3 
#define d4 4 
#define d5 5  
#define d6 6 
#define d7 7 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter.."); 
  lcd.begin(16, 2);
  lcd.print("Oximeter");
    
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
 
 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BPM: ");
        lcd.print(pox.getHeartRate());
        
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
 
 
        tsLastReport = millis();
    }
}
