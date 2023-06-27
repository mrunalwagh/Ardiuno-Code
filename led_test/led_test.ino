
  int led1PinGreen = 2;      //soap out ,first relay start, dealy 5 sec       
   int led2PinRed = 3;      // wait for 20 sec, after 20s res will stop

 

void setup()
{
  // put your setup code here, to run once:
  pinMode(led1PinGreen, OUTPUT);  
  pinMode(led2PinRed, OUTPUT);  


}

//-----------------------------

void loop()
{
  // put your main code here, to run repeatedly:

   digitalWrite(led1PinGreen, HIGH); // Trigger pin to HIGH
    delay(1000);
   digitalWrite(led1PinGreen, LOW); // Trigger pin to HIGH

   delay(2000);
     digitalWrite(led2PinRed, HIGH); // Trigger pin to HIGH
    delay(1000);
   digitalWrite(led2PinRed, LOW); // Trigger pin to HIGH

   
}
//-----------------------------
