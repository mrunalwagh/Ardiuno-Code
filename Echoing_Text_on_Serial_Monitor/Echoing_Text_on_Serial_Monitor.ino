Echoing Text on Serial Monitor
/* Sample code-1 */
/* To transfer Data from Arduino to PC using serial communication*/

void setup() 
{                  
  Serial.begin(9600);             
}

void loop() 
{                                           
  Serial.println("Welcome to InteliDemics"); 
}

Echoing Text on Serial Monitor
/* Sample code-2 */
/* To transfer Data from PC to Arduino using serial communication*/

char ch;
void setup() 
{
   Serial.begin(9600);                                     
}

void loop() 
{
   if(Serial.available()>0)                            
   {
     ch=Serial.read();                                    
     Serial.print("Student has typed:");   
     Serial.print(" ");                                      
     Serial.println(ch);                                   
   }
}
