
#include<SoftwareSerial.h>
SoftwareSerial mton(10,11);
String datavalues;
float temp=10.10;
int range=2;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
mton.begin(9600);
}
//----------------
void loop() 
{
  // put your main code here, to run repeatedly:
  sendValues();
 
  
  delay(3000);;
}

void sendValues()
{
   
Serial.println("\nvalues before uploading to gateway");
Serial.println("\nTempraturevalue is:");
Serial.println(temp);
Serial.println("\n Range value is:");
Serial.println(range);
Serial.println("\n Now sending");
datavalues =String(String(temp)+String(",")+String(range)+String(","));
splitStr(datavalues);

Serial.println("Print data Values array ");
Serial.println(datavalues);
mton.println(datavalues);
Serial.println("Data send sucessfully");


}


//-----------------------------------
void splitStr(String myString)
{
   Serial.println("am in split str");
   int commaIndex = myString.indexOf(',');
   int secondCommaIndex = myString.indexOf(',', commaIndex+1);
   String firstValue = myString.substring(0, commaIndex);
   String secondValue = myString.substring(commaIndex+1,secondCommaIndex);
   Serial.println("Temp");
   Serial.println(firstValue);
   Serial.println("Range");
   Serial.println(secondValue);
   delay(3000);
   
  
}


