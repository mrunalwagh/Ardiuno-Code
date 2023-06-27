//Interfacing and controlling Speed and Direction of Stepper Motor  
/* Sample code (Stepper motor-Clockwise)*/
/*  Interfacing and rotating Stepper Motor (Clockwise)*/
int motorPin1 = 8;                                      // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;                                     // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;                                  // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;                                 // Orange - 28BYJ48 pin 4
                                                                        
void setup() 
{
     pinMode(motorPin1, OUTPUT);
     pinMode(motorPin2, OUTPUT);
     pinMode(motorPin3, OUTPUT);
     pinMode(motorPin4, OUTPUT);
     Serial.begin(9600);
}

void loop()
{
     digitalWrite(motorPin1,HIGH); 
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
     digitalWrite(motorPin4,LOW);
     delay(5);
    
    digitalWrite(motorPin1,LOW);       
    digitalWrite(motorPin2,HIGH);       
    digitalWrite(motorPin3,LOW);
    digitalWrite(motorPin4,LOW);
    delay(5);
    
    digitalWrite(motorPin1,LOW);   
    digitalWrite(motorPin2,LOW);   
   digitalWrite(motorPin3,HIGH);
   digitalWrite(motorPin4,LOW);
   delay(5);
  
  digitalWrite(motorPin1,LOW);   
  digitalWrite(motorPin2,LOW);     
  digitalWrite(motorPin3,LOW);    
  digitalWrite(motorPin4,HIGH);   
  delay(5);
}

Interfacing and controlling Speed and Direction of Stepper Motor  
/* Sample code-2 (Stepper motor-Anti-Clockwise) */
/*  Interfacing and rotating Stepper Motor (Anti-Clockwise)*/
int motorPin1 = 8;                                      // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;                                     // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;                                  // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;                                 // Orange - 28BYJ48 pin 4
                                                                   // Red    - 28BYJ48 pin 5 (VCC)
void setup() 
{
     pinMode(motorPin1, OUTPUT);
     pinMode(motorPin2, OUTPUT);
     pinMode(motorPin3, OUTPUT);
     pinMode(motorPin4, OUTPUT);
     Serial.begin(9600);
}

void loop()
{
     digitalWrite(motorPin1,HIGH); 
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
     digitalWrite(motorPin4,LOW);
     delay(5);
    
    digitalWrite(motorPin1,LOW);       
    digitalWrite(motorPin2,LOW);       
    digitalWrite(motorPin3,LOW);
    digitalWrite(motorPin4, HIGH);
    delay(5);
    
    digitalWrite(motorPin1,LOW);    
    digitalWrite(motorPin2,LOW);   
    digitalWrite(motorPin3,HIGH);
    digitalWrite(motorPin4,LOW);
    delay(5);
  
   digitalWrite(motorPin1,LOW);    
   digitalWrite(motorPin2, HIGH);     
   digitalWrite(motorPin3,LOW);      
   digitalWrite(motorPin4,LOW);   
   delay(5);
}
