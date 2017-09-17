#include "EEPROM.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include <Fonts/FreeSerif9pt7b.h>
// Color definitions
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
#define __CS 7
#define __DC 9
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC,8);
#define VT_PIN A0 
#define AT_PIN A1
#define minus 5
#define plus  4 

//int out =10;
int h=0;
int prevh = 0;
unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
float sumacurent = 0.; // valoare insumare curent pentru calcul medie

int trcurent = 0;
int trtensiune = 0;

float current = 0.;   // valoare curent
float tensiune = 0.; // valoare tensiune
int tempPin = A3;
int val;

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
pinMode(10, OUTPUT);
h=EEPROM.read(100);
analogWrite(10, h);
 tft.begin();
   tft.fillScreen();
 //setupPWM16();
//if ((h < 0) || (h > 65535))
//if ((h < 0) || (h > 255))
//{h = 1;
//}
}
//uint16_t icr = 0xffff;
void loop()
{
 // if (digitalRead(plus) ==HIGH)
 h=EEPROM.read(100);
analogWrite(10, h);
 printt();
 //else
 if (digitalRead(plus) == LOW)

    {



      
    h = h+1;
   
     if (h > 255) {h=254;}
   // Serial.println(h);
  // Serial.println(h);
analogWrite(10, h);
    delay(150);
   // if(h != prevh)
 // {
  //  prevh =h;
  //  print();delay(5000);
Serial.println(h);}


   // delay(150);
    EEPROM.write(100, h);
    // }

     if (digitalRead(minus) == LOW)

    {



      
    h = h-1;
     if (h < 0) {h=1;}
   // Serial.println(h);
  // Serial.println(h);
analogWrite(10, h);
    delay(150);
 //   if(h != prevh)
//  {
  //  prevh =h;
  //  print();delay(5000);
Serial.println(h);}


   // delay(150);
   EEPROM.write(100, h);
   //  }
     
}

void printt()
{
 sumatensiune = 0;
  sumacurent = 0;
    for (int i=1; i <= 20; i++)
  {
 trtensiune = analogRead(VT_PIN);
 sumatensiune = sumatensiune + trtensiune;
  trcurent = analogRead(AT_PIN);

  sumacurent = sumacurent + trcurent;
delay (20);  // pauza de 20ms intre masuratori
    }

// calculam valorile medii
sumacurent = sumacurent/20.;
sumatensiune = sumatensiune/20.;
  tensiune = sumatensiune * (5.0 / 1024.0) * 5.0;
 // voltage=tensiune
  current = sumacurent * (5.1 / 1024.0);
 // current=curent
  
//  float watts = 18.3-voltage * current;
 // sumatensiune=sumatensiune+voltage;
 // sumacurent=sumacurent+current;
delay(20);
  val = analogRead(tempPin);
float mv = ( val/1024.0)*5100; 
float cel = mv/10;
  
  
  
  
  
  
  
  
  /*
  int vt_read = analogRead(VT_PIN);
  int at_read = analogRead(AT_PIN);

  float voltage = vt_read * (5.0 / 1024.0) * 5.0;
  float current = at_read * (5.0 / 1024.0);
  float watts = voltage * current;
  */
  tft.setFont(&FreeSerif9pt7b);
  // tft.setTextSize(2);
  // tft.fillRect(0,0,95,35,BLACK);
// tft.setCursor(0,30);tft.setTextSize(2); tft.setTextColor(CYAN, BLACK); 
 
 // tft.fillScreen();
  tft.setCursor(0,30);tft.setTextSize(2);tft.fillRect(0,0,95,35,BLACK); tft.setTextColor(CYAN, BLACK); 
   //
   tft.print(tensiune);
   tft.setCursor(100,30);
    tft.setTextSize(2);tft.println("V"); 
 
 // else
 // tft.setCursor(0,30);tft.setTextSize(2); tft.setTextColor(CYAN, BLACK);tft.fillRect(0,0,128,35,BLACK); tft.print(voltage);
  
    
   tft.setTextColor(YELLOW,BLACK); 
   tft.fillRect(0,40,95,35,BLACK);
   tft.setCursor(23,68);tft.setTextSize(2);
  tft.print(current);tft.setCursor(100,67);tft.setTextSize(2);tft.println("A");  
  
  tft.setTextColor(RED,BLACK); 
  tft.setCursor(5,105);tft.setTextSize(2); tft.fillRect(0,80,92,30,BLACK);
 tft.print(cel);
tft.setCursor(100,105);
tft.setTextSize(2);tft.println("C");
   tft.drawCircle(95, 85, 2, RED);
    tft.setFont();
   tft.setTextSize(1); tft.setTextColor(GREEN,BLACK); tft.setCursor(10,115);tft.println("Power meter V 1.02");
//delay(5000);


   if (cel > 40)
  {digitalWrite(6, HIGH); }
  
  
  if (cel < 35)
  digitalWrite(6, LOW);
  
  delay(500);
}

