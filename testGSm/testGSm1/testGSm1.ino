#include <SoftwareSerial.h>
SoftwareSerial msgSerial(0,1); //tx,rx
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 msgSerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

String str="RING  8766403908";
String workingString = str.substring(0,4);
Serial.println("extracted characters");
Serial.println(workingString);
 if(workingString=="RING")
 {

    Serial.println("String RING detected");
 }
 else
 {

 Serial.println("String RING not detected");
  
 }
 

 gsmTest();
delay(1000);

}


void gsmTest()
{

  Serial.println("Test : am in gsm test function ");

   msgSerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();
    delay(1000);
  // msgSerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best  updateSerial();
   //msgSerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  //updateSerial();
   //msgSerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
}
//------------------------------------------------------------

void updateSerial()
{
  Serial.println("Test : am in update serial ");
  delay(500);
  while (Serial.available()) 
   {
    Serial.println("am in while");
     Serial.println(Serial.read());//Forward what Serial received to Software Serial Port
   }
   
   msgSerial.println("AT"); //Once the handshake test is successful, it will back to OK
 
  while(msgSerial.available()>0) 
  {    
    Serial.println("Test : got data on msgSeriall ");
     String str=String(msgSerial.read());
     Serial.println("extracted complete string");
     Serial.write(msgSerial.read());
     String workingString = str.substring(0,4);
    Serial.println("extracted characters o to 4");
    Serial.println(workingString);
 if(workingString=="RING")
 {

    Serial.println("String RING detected");
 }
 else
 {

 Serial.println("String RING not detected");
  
 }
  }//wnd of while

  
 } //end of fun
