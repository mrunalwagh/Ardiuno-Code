//Writing on SD card using pin10
/* Sample code-1 */
/*  Program to Write data on SD card  */
#include<SPI.h>        //library file for SPI protocol
#include<SD.h>         //library file for SD card
int csPin = 10;        // connect cs pin of SD card to Arduino Pin 10
File myFile;           //declaration of file
unsigned long time;    //initialize variable

void setup()
{
  Serial.begin(9600);       // set baud rate
  pinMode(csPin, OUTPUT);
  while (!Serial)            // wait for serial port to connect. Needed for native USB port only
  {
    ;
  }
  Serial.println("Initializing SD card....");
  if (!SD.begin(csPin))                         // check connection of SD card
  {
    Serial.println("Initialization failed.");   // condition true then not initialized SD
    return;
  }
  Serial.println("Initialization done");
}

void loop()
{
  myFile = SD.open("InteliDemics.txt", FILE_WRITE);        // Creates new txt file having the given name;
  time = millis();                                         //internal clock or synchronization of arduino board
  if (myFile)                                            // if file is created successfully, then write to it
  {
    Serial.print("Writing in InteliDemics.txt...");
    myFile.println("Welcome to InteliDemics");         //write some text in the txt file using serial monitoring
    myFile.close();                                    // close the txt file:
    Serial.println("Writing in file is done.");
  }
  else
  {
    Serial.println("Could not write in the file.");
  }
  delay(10000);
}
//Reading from SD card using pin10
/* Sample code-1 */
/*  Program to Read data from  SD card  */
#include<SPI.h>     //library file for SPI protocol
#include<SD.h>      //library file for SD card
File myFile;           //declaration of file
int csPin = 10;      // connect cs pin of SD card to Arduino Pin 10

void setup()
{
  Serial.begin(9600);                      // set baud rate
  pinMode(csPin, OUTPUT);
  while (!Serial)                                // wait for serial port to connect. Needed for native USB port only
  {
    ;
  }
  Serial.println("Initializing SD card....");

  if (!SD.begin(csPin))                         // check connection of SD card
  {
    Serial.println("Initialization failed.");   // condition true then not initialized SD
    return;
  }
  Serial.println("Initialization done");
}

void loop()
{
  myFile = SD.open("InteliDemics.txt", FILE_READ);    // Opens the file for reading;
  if (myFile)                                                                         // checks if file is opened successfully or not
  {
    Serial.println("Reading from InteliDemics.txt");

    while (myFile.available())                      // Check the buffer
    {
      Serial.println(myFile.read());              //read the data from txt file and print on serial monitor
    }
    myFile.close();                                    // close the txt file
    Serial.println("Reading from file is done");
  }
  else
  {
    Serial.println("Could not open the file InteliDemics.txt");
  }
}
