#include<SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);//5 6
  char *str;
  char ch;
  int charCounter=0;
  int flagRecvMsg=0;
void setup()

{

  mySerial.begin(9600);   // Setting the baud rate of GSM Module 

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);

}

void loop()
{
  if(flagRecvMsg==0)
  {
Serial.println("\n i am entering into loop");
delay(2000);
  }
  if (Serial.available()>0)

   switch(Serial.read())

  {

    case 's':

      SendMessage();

      break;

    case 'd':

      DialCall();

      break;
      
    case 'r':
Serial.println("\n i am entering into switch receive mode");
 delay(2000);
    RecieveMessage();
      break;

  }

   //read contect only receive messsage is start with # and then give that code to display 

//------------------------------------
 if (mySerial.available()>0)
 {
  Serial.println("\n i am entering into myserial.available if");
 delay(2000);
  ch=mySerial.read();
  if(ch=='#')
  {
    str[charCounter]=='#';
   // call to function which will do parsing 
    funParse(str);
  }
   else
  {
   delay(1000);
   Serial.println(ch);
   str[charCounter++]=ch;
  }
  //Serial.write(mySerial.read());
  //str=ch;
  //str++;
 
 
 }
/*
 if(str!=NULL)
 {
Serial.println("\n COllected string is :");
Serial.println(str);

 }
 */
 //-------------------------
}

 void SendMessage()


{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+917588068825\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.write("I am SMS from GSM Module");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
 
  delay(1000);
   
  Serial.println("message send successfully");

}

 void RecieveMessage()

{

  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS

  delay(1000);
  charCounter=0;
  flagRecvMsg=1;
  Serial.println("\nflagRecvMsg=1 set\n ");

}



  void DialCall()

 {

  mySerial.println("ATD+917588068825;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);

 }

 //---------------------parsing function

 void funParse(char *str)
 {
Serial.println("\n I am entr in parsing function ");
Serial.println("\n I received complete message as follow ");
Serial.println(str);
Serial.println("\n\n");

 }

//------------------------------------end of parsing function
