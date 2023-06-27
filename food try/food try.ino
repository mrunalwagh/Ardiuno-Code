//#include<LiquidCrystal.h>            ////lcd display library

//LiquidCrystal //lcd(8,9,10,11,12,13);
/********Define_States****************/
#include <Wire.h>// i2c //lcd
#include <LiquidCrystal_I2C.h> // Library for //lcd
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
SoftwareSerial BT(10, 11); //TX, RX  pins of arduino respetively
#define MQ3 5
#define BUZZER 12
#define Milk_time 10
#define Food_Plate_time 10
#define Cold_Coffe_time 50
#define Wine_Glass_time 60
#define Curry_bowl_time 36
#define Banana_time 20
#define Apple_time 20
#define Sandwich_time 20
#define Orange_time 20
#define Hotdog_time 20
#define Pizza_time 20
#define Donut_time 20
#define Cake_time 20
#define Coriander_time 20
int MQ3_State = 0;
String command;
String incomingData;   // for storing incoming serial data
String message = "";  
int cont=0;
int Milk_Count=0;
int Food_Plate_Count=0;
int Wine_Glass_Count=0;
int Cold_Coffe_Count=0;
int Curry_bowl_Count=0;
int Banana_Count=0;
int Apple_Count=0;
int Sandwich_Count=0;
int Orange_Count=0;
int Hotdog_Count=0;
int Pizza_Count=0;
int Donut_Count=0;
int Cake_Count=0;
int Coriander_Count=0;
/**********************************************Item detection**********************************/
int Milk=false;
int Food_Plate=false;
int Wine_Glass=false;
int Cold_Coffe=false;
int Curry_bowl=false;
int Banana=false;
int Apple=false;
int Sandwich=false;
int Orange=false;
int Hotdog=false;
int Pizza=false;
int Donut=false;
int Cake=false;
int Coriander=false;
/***********************************************************************************************************************/
float value = 3035;                   //Preload timer value (3035 for 4 seconds)
enum Product_type
{
  Milk_Item,
  Food_Plate_Item,
 Wine_Glass_Item,
 Cold_Coffe_Item,
 Curry_bowl_Item,
 Banana_Item,
 Apple_Item,
 Sandwich_Item,
 Orange_Item,
 Hotdog_Item,
 Pizza_Item,
 Donut_Item,
 Cake_Item,
 Coriander_Item,
};

enum Product_type Product_Item;

void setup()
{
   pinMode(MQ3, INPUT);
   pinMode(BUZZER, OUTPUT);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.clear();
   Serial.begin(115200);
   BT.begin(115200);
 BT.println("system milk item");
  //pinMode(ledPin, OUTPUT);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("FOOD SAFETY IN ");
lcd.setCursor(0, 1);
lcd.print("REFRIGERATOR");
delay(300);
digitalWrite(BUZZER,HIGH);
    delay(1000);
    digitalWrite(BUZZER,LOW);
  
  noInterrupts();                       // disable all interrupts
  
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = value;                        // preload timer
  TCCR1B |= (1 << CS10)|(1 << CS12);    // 1024 prescaler 
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();                         // enable all interrupts
}

void receive_message()
{
  if (BT.available() > 0)
  {
    incomingData = BT.readString(); // Get the data from the serial port.
    Serial.print(incomingData); 
    delay(10); 
  }
}

ISR(TIMER1_OVF_vect)                    // interrupt service routine for overflow
{
  TCNT1 = value;                                // preload timer
  cont++;


 if(Milk==true)
 {
  Milk_Count++;
 }
 else if( Food_Plate==true)
 {
  Food_Plate_Count++;
 }
 else if(Wine_Glass==true)
 {
  Wine_Glass_Count++;
 }
 else if(Cold_Coffe==true)
 {
   Cold_Coffe_Count++;
 }
 else if(Curry_bowl==true)
 {
  Curry_bowl_Count++;
 }
 else if(Banana==true)
 {
  Banana_Count++;
 }
 else if(Apple==true)
 {
  Apple_Count++;
 }
 else if(Sandwich==true)
 {
  Sandwich_Count++;
 }
 else if(Orange==true)
 {
  Orange_Count++;
 }
 else if(Hotdog==true)
 {
  Hotdog_Count++;
 }
  else if(Pizza==true)
 {
  Pizza_Count++;
 }
  else if(Donut==true)
  {
  Donut_Count++;
  }
  else if(Cake==true)
  {
  Cake_Count++;
  }
  else if(Coriander==true)
  {
  Coriander_Count++;
  }
}

void loop()
{
   //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("ITEM");
    //lcd.setCursor(0, 1);
    //lcd.print("SCANNING");

 receive_message();

   switch(Product_Item)
  {
    case Milk_Item:
    //  BT.println("milk item");
      // Serial.println("milk item ");
    if(Milk_Count==0&&incomingData.indexOf("milk bottle")>=0&&Milk==false)
    {
//       lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("MILK");
//    lcd.setCursor(0, 1);
//    lcd.print("IN LIST");
            Serial.println("milk item avilable");
                   delay(1000);
                   incomingData="";


      Milk=true;//milk detected
    }
    else if(Milk_Count>= Milk_time&& Milk==true)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MILK");
    lcd.setCursor(0, 1);
    lcd.print("SPOILAGE");
    digitalWrite(BUZZER,HIGH);
    delay(1000);
    digitalWrite(BUZZER,LOW);
    //delay(300);

       Serial.println("Product expire");
       Milk=false;
       Milk_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Milk_Count < Milk_time&& Milk==true)
    {
      Serial.println("milk list");
             delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MILK");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MILK");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
             

      ////lcd display item milk displat =true
    }
    else
    {
      Milk=false;
      
    }
    Product_Item=Food_Plate_Item;
    break;
    case Food_Plate_Item:
    //  BT.println("Food plate item");
     //  Serial.println("Food plate item ");
    if(Food_Plate_Count==0&&incomingData.indexOf("Food plate")>=0&&Food_Plate==false)
    {
            Serial.println("Food plate item avilable");
                   delay(1000);
                   incomingData="";


      Food_Plate=true;//milk detected
    }
    else if(Food_Plate_Count>= Food_Plate_time&& Food_Plate==true)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FOOD PLATE");
    lcd.setCursor(0, 1);
    lcd.print("SPOILAGE");
    digitalWrite(BUZZER,HIGH);
    delay(1000);
    digitalWrite(BUZZER,LOW);
    //delay(300);


       Serial.println("Food plate expire");
       Food_Plate=false;
       Food_Plate_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Food_Plate_Count < Food_Plate_time&& Food_Plate==true)
    {
      Serial.println("Food plate in list");
                 delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FOOD PLATE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FOOD PLATE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
    }
    else
    {
      Food_Plate=false;
      
    }
    Product_Item=Wine_Glass_Item;
   
    break;
      case Wine_Glass_Item:
    //  BT.println("Food plate item");
    //    Serial.println("Wine glass ");
    if(Wine_Glass_Count==0&&incomingData.indexOf("wine glass")>=0&&Wine_Glass==false)
    {
            Serial.println("Wine glass avilable");
                   delay(1000);
                   incomingData="";


      Wine_Glass=true;//milk detected
    }
    else if(Wine_Glass_Count>= Wine_Glass_time&& Wine_Glass==true)
    { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WINE GLASS");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
       Serial.println("Wine_Glass expire");
       Wine_Glass=false;
      Wine_Glass_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Wine_Glass_Count < Wine_Glass_time&& Wine_Glass==true)
    {
      Serial.println("Wine_Glass in list");
           //  delay(1000);
         delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WINE GLASS");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WINE GLASS");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      ////lcd display item milk displat =true
    }
    else
    {
      Wine_Glass=false;
      
    }
    Product_Item=Cold_Coffe_Item;
   
    break;
      case Cold_Coffe_Item:
  //    BT.println("cold item");
   //   Serial.println("Cold_Coffe ");
    if(Cold_Coffe_Count==0&&incomingData.indexOf("cold coffee")>=0&&Cold_Coffe==false)
    {
            Serial.println("Cold_Coffe avilable");
                   delay(1000);
                   incomingData="";


      Cold_Coffe=true;//milk detected
    }
    else if(Cold_Coffe_Count>= Cold_Coffe_time&& Cold_Coffe==true)
    {
         lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("COLD COFFEE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Cold_Coffe expire");
       Cold_Coffe=false;
       Cold_Coffe_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Cold_Coffe_Count < Cold_Coffe_time&& Cold_Coffe==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("COLD COFFEE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("COLD COFFEE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Cold_Coffe in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Cold_Coffe=false;
      
    }
    Product_Item= Curry_bowl_Item;
   
    break;
    //1
       case  Curry_bowl_Item:
    //  BT.println("Food plate item");
     // Serial.println(" Curry_bowl ");
    if( Curry_bowl_Count==0&&incomingData.indexOf("curry bowl")>=0&& Curry_bowl==false)
    {
            Serial.println(" Curry_bowl avilable");
                   delay(1000);
                   incomingData="";


       Curry_bowl=true;//milk detected
    }
    else if( Curry_bowl_Count>=  Curry_bowl_time&&  Curry_bowl==true)
    {
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CURRY BOWL");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println(" Curry_bowl expire");
        Curry_bowl=false;
       Curry_bowl_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if( Curry_bowl_Count <  Curry_bowl_time&&  Curry_bowl==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CURRY BOWL");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CURRY BOWL");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println(" Curry_bowl in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
       Curry_bowl=false;
      
    }
    Product_Item= Banana_Item;
   
    break;
    //2
     case  Banana_Item:
   //   BT.println(" Banana item");
    //   Serial.println(" Banana ");
    if( Banana_Count==0&&incomingData.indexOf("banana")>=0&& Banana==false)
    {
            Serial.println(" Banana avilable");
                   delay(1000);
                   incomingData="";


       Banana=true;//milk detected
    }
    else if( Banana_Count>=Banana_time&&Banana==true)
    {
         lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BANANA");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println(" Banana expire");
        Banana=false;
        Banana_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if( Banana_Count <  Banana_time&&  Banana==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BANANA");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BANANA");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println(" Banana in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
       Banana=false;
      
    }
    Product_Item=Apple_Item;
   
    break;
    //3
          case Apple_Item:
   //   BT.println("apple item");
    //      Serial.println("Apple ");
    if(Apple_Count==0&&incomingData.indexOf("apple")>=0&&Apple==false)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("APPLE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
      delay(2000);
            Serial.println("Apple avilable");
                   delay(1000);
                   incomingData="";


      Apple=true;//milk detected
    }
    else if(Apple_Count>= Apple_time&& Apple==true)
    {
          lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("APPLE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(2000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Apple expire");
       Apple=false;
       Apple_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Apple_Count < Apple_time&& Apple==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("APPLE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("APPLE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Apple in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Apple=false;
      
    }
    Product_Item=Sandwich_Item;
   
    break;
    //4
          case Sandwich_Item:
    //  BT.println("sandwich item");
    //   Serial.println("Sandwich");
    if(Sandwich_Count==0&&incomingData.indexOf("sandwich")>=0&&Sandwich==false)
    {
            Serial.println("Sandwich avilable");
                   delay(1000);
                   incomingData="";


      Sandwich=true;//milk detected
    }
    else if(Sandwich_Count>= Sandwich_time&& Sandwich==true)
    {
       lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SANDWICH");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Sandwich expire");
       Sandwich=false;
       Sandwich_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Sandwich_Count < Sandwich_time&& Sandwich==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SANDWICH");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SANDWICH");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Sandwich in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Sandwich=false;
      
    }
    Product_Item=Orange_Item;
   
    break;
    //5
          case Orange_Item:
    //  BT.println("ORANGE item");
    //    Serial.println("Orange ");
    if(Orange_Count==0&&incomingData.indexOf("orange")>=0&&Orange==false)
    {
            Serial.println("Orange avilable");
                   delay(1000);
                   incomingData="";


      Orange=true;//milk detected
    }
    else if(Orange_Count>= Orange_time&& Orange==true)
    {
       lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ORANGE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Orange expire");
       Orange=false;
       Orange_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Orange_Count < Orange_time&& Orange==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ORANGE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ORANGE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Orange in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Orange=false;
      
    }
    Product_Item=Hotdog_Item;
   
    break;
    //6
          case Hotdog_Item:
   //   BT.println("Hotdog item");
  //     Serial.println("Hotdog ");
    if(Hotdog_Count==0&&incomingData.indexOf("hot dog")>=0&&Hotdog==false)
    {
            Serial.println("Hotdog avilable");
                   delay(1000);
                   incomingData="";


      Hotdog=true;//milk detected
    }
    else if(Hotdog_Count>= Hotdog_time&& Hotdog==true)
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HOTDOG");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
       Serial.println("Hotdog expire");
       Hotdog=false;
       Hotdog_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Hotdog_Count < Hotdog_time&& Hotdog==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HOTDOG");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HOTDOG");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Hotdog in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Hotdog=false;
      
    }
    Product_Item=Pizza_Item;
   
    break;
    //7
          case Pizza_Item:
   //   BT.println("PIZZA item");
  //     Serial.println("Pizza ");
    if(Pizza_Count==0&&incomingData.indexOf("pizza")>=0&&Pizza==false)
    {
            Serial.println("Pizza avilable");
                   delay(1000);
                   incomingData="";


      Pizza=true;//milk detected
    }
    else if(Pizza_Count>= Pizza_time&& Pizza==true)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIZZA");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Pizza expire");
       Pizza=false;
       Pizza_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Pizza_Count < Pizza_time&& Pizza==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIZZA");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIZZA");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Pizza in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Pizza=false;
      
    }
    Product_Item=Donut_Item;
   
    break;
    //8
          case Donut_Item:
    //  BT.println("donut item");
   //   Serial.println("Donut");
    if(Donut_Count==0&&incomingData.indexOf("donut")>=0&&Donut==false)
    {
            Serial.println("Donut avilable");
                   delay(1000);
                   incomingData="";


      Donut=true;//milk detected
    }
    else if(Donut_Count>= Donut_time&& Donut==true)
    {
       lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DONUT");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Donut expire");
       Donut=false;
       Donut_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Donut_Count < Donut_time&& Donut==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DONUT");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DONUT");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Donut in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Donut=false;
      
    }
    Product_Item=Cake_Item;
   
    break;
            case Cake_Item:
  //    BT.println("cake item");
    //     Serial.println("cake");
    if(Cake_Count==0&&incomingData.indexOf("cake")>=0&&Cake==false)
    {
            Serial.println("cake avilable");
                   delay(1000);
                   incomingData="";


      Cake=true;//milk detected
    }
    else if(Cake_Count>= Cake_time&& Cake==true)
    {
          lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CAKE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("cake expire");
       Cake=false;
       Cake_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Cake_Count < Cake_time&& Cake==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CAKE");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CAKE");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Cake in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Cake=false;
      
    }
    Product_Item=Coriander_Item;
   
    break;
    case Coriander_Item:
 //     BT.println("coriander item");
  //      Serial.println("Coriander");
    if(Coriander_Count==0&&incomingData.indexOf("coriander")>=0&&Coriander==false)
    {
            Serial.println("Coriander avilable");
                   delay(1000);
                   incomingData="";


      Coriander=true;//milk detected
    }
    else if(Coriander_Count>= Coriander_time&& Coriander==true)
    {
         lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CORIANDER");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);

       Serial.println("Coriander expire");
       Coriander=false;
       Coriander_Count=0;
       delay(1000);
     //expire notification please check milk in the fridge only
      
    }
   else if(Coriander_Count < Coriander_time&& Coriander==true)
    {
               delay(1000);
             MQ3_State=digitalRead(MQ3);
    if (MQ3_State == LOW) {
    // turn LED on:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CORIANDER");
      lcd.setCursor(0, 1);
      lcd.print("SPOILAGE");
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CORIANDER");
      lcd.setCursor(0, 1);
      lcd.print("IN LIST");
  }
      Serial.println("Coriander in list");
           //  delay(1000);

      ////lcd display item milk displat =true
    }
    else
    {
      Coriander=false;
      
    }
    Product_Item= Milk_Item;
    break;
    default : 
      break;
  }
  }
 
