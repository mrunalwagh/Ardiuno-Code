

int trigPin = 4;
int echoPin = 5;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);        // set baud rate;
}

void loop()
{
  digitalWrite(trigPin, LOW);                            // set the pin low;
  delay(2);
  digitalWrite(trigPin, HIGH);                       //set the trigger high to provide a bus;
  delay(10);
  digitalWrite(trigPin, LOW);                         // set the pin low;
  int duration = pulseIn(echoPin, HIGH);    //used to check duration of wave (tx & rx);
  int distance = (duration * 0.034) / 2;          //formula to calculate distance;
  float feet = distance / 30.48;                     // distance in feet;
  Serial.print("Distance in feet is: ");
  Serial.println(feet);                                       // print on serial monitor;
  delay(1000);
}
