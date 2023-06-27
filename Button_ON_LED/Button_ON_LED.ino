int pinButton = 9;
int mtr = 13;
int stateLED = LOW;
int stateButton;
int previous = LOW;
long time = 0;
long debounce = 200;

void setup() {
  pinMode(pinButton, INPUT);
  pinMode(mtr, OUTPUT);
}

void loop() {
  stateButton = digitalRead(pinButton);  
  if(stateButton == HIGH && previous == LOW) //&& millis() - time > debounce)
  {
    if(stateLED == HIGH)
    {
      stateLED = LOW; 
    } else 
    {
       stateLED = HIGH; 
    }
    //time = millis();
  }
  //digitalWrite(mtr, HIGH);
  previous == stateButton;
}
