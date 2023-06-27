Interfacing LED Bar with Arduino
/* Sample code-1 */
/* Program to make single LED ON and OFF on LED bar  */

int led1Pin=2;

void setup() 
{                                                           
  pinMode(led1Pin,  OUTPUT);           
}

void loop()
{                              
  digitalWrite(led1Pin,HIGH);          
  delay(1000);                                   
  digitalWrite(led1Pin,LOW);        
  delay(1000);                                 
}

Interfacing LED Bar with Arduino
/* Sample code-2 */
/* Make the LEDs on LED bar ON and OFF */

int led1Pin = 2;              
int led2Pin = 3;
int led3Pin = 4;
int led4Pin = 5;
int led5Pin = 6;
int led6Pin = 7;
int led7Pin = 8;
int led8Pin = 9;

void setup()
{
  pinMode(led1Pin, OUTPUT);      
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  pinMode(led8Pin, OUTPUT);
}

void loop()
{
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led3Pin, HIGH);
  digitalWrite(led4Pin, HIGH);
  digitalWrite(led5Pin, HIGH);
  digitalWrite(led6Pin, HIGH);
  digitalWrite(led7Pin, HIGH);
  digitalWrite(led8Pin, HIGH);
  delay(1000);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
  digitalWrite(led5Pin, LOW);
  digitalWrite(led6Pin, LOW);
  digitalWrite(led7Pin, LOW);
  digitalWrite(led8Pin, LOW);
  delay(1000);
}
