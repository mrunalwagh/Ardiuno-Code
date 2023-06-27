
#include<SoftwareSerial.h>
SoftwareSerial mton(10,11);
char datavalues[400];
float temp=10;
int range=2;
void setup()
{
  // put your setup code here, to run once:
mton.begin(9600);
}
//----------------
void loop() 
{
  // put your main code here, to run repeatedly:
  sendValues();
 
  
  delay(1000);;
}

void sendValues()
{
   char s
   char countvalueTemp[8];
char countvalueRange[8];
 
dtostrf(range, 4, 2, countvalueRange);
dtostrf(temp, 4, 2, countvalueTemp);
Serial.println("\nvalues before uploading to gateway");
Serial.println("\nTempraturevalue is:");
Serial.println(temp);
Serial.println("\n Range value is:");
Serial.println(range);
Serial.println("\n Now publish");

datavalues =String("coming from arduino: ")+String("R= ")+String(range)+String("T= ")+String(temp);

//snprintf (datavalues, 90, "{\"Temp Value\" :  %s,\"Range Value\" :  %s}", countvalueTemp,countvalueRange); 
Serial.println("Print data Values");
Serial.println(datavalues);
mton.println(str);
Serial.println("Data send sucessfully");
mton.write(datavalues);

}

