Interfacing RTC module and displaying time
/* Sample code-1 */
/* Date and time functions using a DS3231 RTC connected via I2C and Wire lib  */
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup ()
{
  Serial.begin(9600);
  delay(2000); // wait for console opening
  if (! rtc.begin())
  {
    Serial.println(" Couldn't find RTC ");
    while (1);
  }
  if (rtc.lostPower())
  {
    Serial.println(" RTC lost power, let’s set the time! ");
    // January 21, 2014 at 3am you would call:
    rtc.adjust(DateTime(2016, 11, 03, 12, 22, 0));
  }
}

void loop ()
{
  DateTime now = rtc.now();
  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.println(now.day());
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
  delay(1000);
}
