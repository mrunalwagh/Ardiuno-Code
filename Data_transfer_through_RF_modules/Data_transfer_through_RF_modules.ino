//Data transfer through RF modules  
/* Sample code */
/*  Program to transfer data using RF Transmitter (RF-Tx) – using SPI protocol  */

#include <RH_ASK.h>
#include <SPI.h>                   // Required for compilation
#include<string.h>
RH_ASK driver;

void setup()
{
    Serial.begin(9600);            
    if (!driver.init())
    Serial.println("initialization failed");
}

void loop()
{
    const char *msg = " Welcome to InteliDemics ";
    driver.send((byte  *) msg, strlen (msg));
    driver.waitPacketSent ();
    delay(1000);
}

//Data transfer through RF modules  
/ * Sample code */
/*  Program to receive data using RF Receiver (RF-Rx) – using SPI protocol  */

#include <RH_ASK.h>
#include <SPI.h>                 // Required for compilation
RH_ASK driver;

void setup()
{
  Serial.begin(9600);
  if (!driver.init())
  Serial.println("Initialization failed");
}

void loop()
{
  byte buf[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  byte buflen = sizeof(buf);
  if (driver.recv(buf, &buflen))                      // Non-blocking
  {
    // Message with a good checksum received, dump it.
    Serial.print ("Message is: ");
    Serial.println ((char*)buf);
  }
}
