#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte rows = 4;
const byte cols = 3;

char keys[rows][cols]=
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'},
};

byte rowPins[rows]={8,7,6,5};
byte colPins[cols]={4,3,2};

Keypad kpd = Keypad(makeKeymap(keys),rowPins,colPins,rows,cols);

char inputArray [1];
char zero[1] = {'0'};
char one[1] = {'1'};
char two[1] = {'2'};
char three[1] = {'3'};
char four[1] = {'4'};
char five[1] = {'5'};
char six[1] = {'6'};
char seven[1] = {'7'};
char eight[1] = {'8'};
char nine[1] = {'9'};

#define prewash 10
#define mainwash 11
#define resin 12
#define ledPin 13
int i=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(prewash,OUTPUT);
  pinMode(mainwash,OUTPUT);
  pinMode(resin,OUTPUT);
};

void loop()
{
  char key=kpd.getKey();
  if(key)
  {
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);
    inputArray[i]=key;
    i++;
    Serial.print(key);
    if(key=='*')
    {
      Serial.print("WELCOME");
      i=0;
    }
    if(key=='#')
    {
      Serial.print("Thank You");
      i=0;
    }
    if(i==1)
    {
      {
        if(inputArray[0]==zero[0])
        {
          Serial.print("Default Mode");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Default Mode");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(1);
          digitalWrite(prewash,LOW);
          delay(1);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Default Mode");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(1);
          digitalWrite(mainwash,LOW);
          delay(1);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Default Mode");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(1);
          digitalWrite(resin,LOW);
          delay(1);
        }
        if(inputArray[0]==one[0])
        {
          Serial.print("Mode 1 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 1");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(10);
          digitalWrite(prewash,LOW);
          delay(10);
          Serial.print("Mainwash");
           lcd.setCursor(0, 0);
          lcd.print("Mode 1");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(10);
          digitalWrite(mainwash,LOW);
          delay(10);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 1");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(10);
          digitalWrite(resin,LOW);
          delay(10);
        }
        if(inputArray[0]==two[0])
        {
          Serial.print("Mode 2 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 2");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(100);
          digitalWrite(prewash,LOW);
          delay(100);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 2");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(100);
          digitalWrite(mainwash,LOW);
          delay(100);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 2");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(100);
          digitalWrite(resin,LOW);
          delay(100);
        }if(inputArray[0]==three[0])
        {
          Serial.print("Mode 3 ");
          Serial.print("Prewash"); 
          lcd.setCursor(0, 0);
          lcd.print("Mode 3");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(110);
          digitalWrite(prewash,LOW);
          delay(110);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 3");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(110);
          digitalWrite(mainwash,LOW);
          delay(110);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 3");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(110);
          digitalWrite(resin,LOW);
          delay(110);
        }
        if(inputArray[0]==four[0])
        {
          Serial.print("Mode 4 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 4");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(110);
          digitalWrite(prewash,LOW);
          delay(110);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 4");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(110);
          digitalWrite(mainwash,LOW);
          delay(110);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 4");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(110);
          digitalWrite(resin,LOW);
          delay(110);
        }
        if(inputArray[0]==five[0])
        {
          Serial.print("Mode 5 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 5");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(120);
          digitalWrite(prewash,LOW);
          delay(120);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 5");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(120);
          digitalWrite(mainwash,LOW);
          delay(120);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 5");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(120);
          digitalWrite(resin,LOW);
          delay(120);
        }
        if(inputArray[0]==six[0])
        {
          Serial.print("Mode 6 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 6");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(130);
          digitalWrite(prewash,LOW);
          delay(130);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 6");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(130);
          digitalWrite(mainwash,LOW);
          delay(130);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 6");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(130);
          digitalWrite(resin,LOW);
          delay(130);
        }
        if(inputArray[0]==seven[0])
        {
          Serial.print("Mode 7 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 7");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(140);
          digitalWrite(prewash,LOW);
          delay(140);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 7");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(140);
          digitalWrite(mainwash,LOW);
          delay(140);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 7");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(140);
          digitalWrite(resin,LOW);
          delay(140);
        }
        if(inputArray[0]==eight[0])
        {
          Serial.print("Mode 8 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 8");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(150);
          digitalWrite(prewash,LOW);
          delay(150);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 8");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(150);
          digitalWrite(mainwash,LOW);
          delay(150);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 8");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(150);
          digitalWrite(resin,LOW);
          delay(150);
        }
        if(inputArray[0]==nine[0])
        {
          Serial.print("Mode 9 ");
          Serial.print("Prewash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 9");
          lcd.setCursor(0, 1);
          lcd.print("Prewash");
          digitalWrite(prewash,HIGH);
          delay(160);
          digitalWrite(prewash,LOW);
          delay(160);
          Serial.print("Mainwash");
          lcd.setCursor(0, 0);
          lcd.print("Mode 9");
          lcd.setCursor(0, 1);
          lcd.print("Mainwash");
          digitalWrite(mainwash,HIGH);
          delay(160);
          digitalWrite(mainwash,LOW);
          delay(160);
          Serial.print("Resin");
          lcd.setCursor(0, 0);
          lcd.print("Mode 9");
          lcd.setCursor(0, 1);
          lcd.print("Resin");
          digitalWrite(resin,HIGH);
          delay(160);
          digitalWrite(resin,LOW);
          delay(160);
        }
      }
    }
    Serial.print("END");
    lcd.setCursor(0, 0);
    lcd.print("THANK YOU");
    lcd.setCursor(0, 1);
    lcd.print("BYR");
    i=0;
  }
}