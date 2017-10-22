#include "EEPROM.h"
#include <SPI.h>
#include <Wire.h>

#include <UTFT.h>

UTFT tft(QD220A,11,13,9,7,8); 

#define VT_PIN A6 
#define VTI_PIN A3 
#define AT_PIN A1
#define minus 5
#define plus  4 
#define fast  3 

int h=0;
int prevh = 0;
unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
float sumacurent = 0.; // valoare insumare curent pentru calcul medie
float sumatensiunei = 0.;
int trcurent = 0;
int trtensiune = 0;
int trtensiunei = 0;
float current = 0.;   // valoare curent iesire
float tensiune = 0.; // valoare tensiune iesire
float tensiunei = 0.; // valoare tensiune intrare
int tempPin = A2;  //LM35
int val;
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void setup()
{
  Serial.begin(9600);
  
   Wire.begin();
   pinMode(6, OUTPUT);
   digitalWrite(6, HIGH);
   pinMode(plus, INPUT); 
pinMode(minus, INPUT);
digitalWrite(plus, HIGH);
digitalWrite(minus, HIGH);
 pinMode(fast, INPUT); 
digitalWrite(fast, HIGH);
pinMode(10, OUTPUT);
analogReference(INTERNAL);
h=EEPROM.read(100);
analogWrite(10, h);

  tft.InitLCD(); 
    tft.clrScr(); 
    tft.setBackColor(0,0,0);
    
}

void loop()
{
 h=EEPROM.read(100);
analogWrite(10, h);
 printt();
 if (digitalRead(plus) == LOW)
    { 
    h = h+1;
   
     if (h > 255) {h=254;}
   
analogWrite(10, h);
    delay(50);
   
//Serial.println(h);
}

    EEPROM.write(100, h);
    
if(!digitalRead(plus) && !digitalRead(fast))
    {  
    h = h+10;
   
     if (h > 255) {h=254;}
  
analogWrite(10, h);
    delay(50);
  
}

    EEPROM.write(100, h);
    // }

if(!digitalRead(minus) && !digitalRead(fast))
    {
   
    h = h-10;
   
     if (h < 0) {h=1;}
   
analogWrite(10, h);
    delay(50);
 
//Serial.println(h);
}


    EEPROM.write(100, h);
    // }
     if (digitalRead(minus) == LOW)

    {  
    h = h-1;
     if (h < 0) {h=1;}
  
analogWrite(10, h);
    delay(50);
 
//Serial.println(h);
}
   
   EEPROM.write(100, h);
   //  } 
}

void printt()
{
 sumatensiune = 0;
 sumatensiunei = 0;
  sumacurent = 0;
    for (int i=1; i <= 20; i++)
  {
 trtensiune = analogRead(VT_PIN);
 sumatensiune = sumatensiune + trtensiune;
  trcurent = analogRead(AT_PIN);

  sumacurent = sumacurent + trcurent;
delay (20);  // pauza de 20ms intre masuratori

trtensiunei = analogRead(VTI_PIN);
sumatensiunei = sumatensiunei + trtensiunei;
    }

// calculam valorile medii
sumacurent = sumacurent/20.;
sumatensiune = sumatensiune/20.;
sumatensiunei = sumatensiunei/20.;
 tensiune= (sumatensiune*((214.4+3.8)/3.8)*1/1024);
  tensiunei = sumatensiunei*(49/.964)*1/1024;
  current = (sumacurent * (1.1 / 1023.0))/0.22;
 
delay(20);
  val = analogRead(tempPin);
float mv = ( val/1024.0)*1000; 
float cel = mv/10;
  

 tft.setBackColor(0,0,0);
 tft.setColor(0,255 , 255);
 tft.drawRect(0,1,219,23);
tft.setFont(BigFont);
tft.setColor(0,0 , 0);
 tft.fillRect(1,2,120,22);
 tft.setColor(0,255 , 255);
   tft.print(String(tensiune),5,5);
    tft.print("V",85,5);
    tft.setFont(SmallFont);
      tft.print("U-iesire",155,7);
 tft.setFont(BigFont);
tft.setColor(0,0 , 255);
 tft.drawRect(0,26,219,50);
  tft.print(String(current),5,30);
  tft.print("A",85,30);  
  tft.setFont(SmallFont);
      tft.print("I-iesire",155,32);
 tft.setFont(BigFont);
 tft.setColor(255,0 , 0);
 tft.drawRect(0,54,219,76);
 tft.print(String(cel),5,57);
tft.drawRoundRect(90,58,95,63);
tft.print("C ",97,57);
 tft.setFont(SmallFont); 
 tft.print("Temperatura",131,58); tft.setFont(BigFont);
 tft.setColor(255,255 , 0);
 tft.drawRect(0,79,219,100);
  tft.setColor(0,0 , 0);
 tft.fillRect(1,80,120,99);
 tft.setColor(255,255 , 0);
   tft.printNumI(h,5,81);
  tft.setFont(SmallFont); 
  tft.print("PWM 8 Bit",145,83);tft.setFont(BigFont);
 tft.setColor(255,0 ,255);
 tft.drawRect(0,103,219,122);
  tft.print(String(tensiunei),5,105);
   tft.print("V",85,105); 
   tft.setFont(SmallFont); 
 tft.print("U-intrare",145,107); tft.setFont(BigFont);

   if (cel > 45)
  {digitalWrite(6, HIGH); }
  if (cel < 35)
  digitalWrite(6, LOW);
  delay(500);
}

