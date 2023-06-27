/* Sample code-1 */
/* Finding pressure using Barometric Pressure sensor(Warning:- Connect vcc pin of sensor to 3.3 v of Arduino
) */
/* Barometer Altitude for Nashik is 700meter */

#include <SFE_BMP180.h>
#include <Wire.h>
#define ALTITUDE 700.0
SFE_BMP180 pressure; //  SFE_BMP180 object, here called "pressure":

void setup()
{
  Serial.begin(9600);
  if (pressure.begin())
  {
    Serial.println("BMP180 init success");
  }
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while (1);                             // Pause forever.
  }
}

void loop()
{
  char status;
  double T, P, p0, a, p1;

  // Printing ALTITUDE in Meters
  Serial.println();
  Serial.print("provided altitude is: ");
  Serial.print(ALTITUDE, 0);
  Serial.println(" meters ");
  // You must first get a temperature measurement to perform pressure reading.
  // finding and Printing Temperature & Absolute Pressure
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(1000);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T, 2);
      Serial.println(" deg C, ");
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is unsuccessful, 0 is returned.
      status = pressure.startPressure(3);
      if (status != 0)
      {

        delay(1000);// Wait for the measurement to complete:
        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P, 2);
          Serial.println(" mb, ");

          Serial.print("Atmospheric pressure is : ");
          p1 = P / pow((1 - (ALTITUDE / 44330)), 5.255);
          Serial.print(p1, 2);
          Serial.println(" mb, ");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  delay(5000);  // Pause for 5 seconds.
}
