#include "EEPROM.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <TFT_ILI9163C.h>
//#include <Fonts/FreeSerif9pt7b.h>
// Color definitions
//#define  BLACK   0x0000
//#define BLUE    0x001F
//#define RED     0xF800
//#define GREEN   0x07E0
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0  
//#define WHITE   0xFFFF
//#define __CS 7
//#define __DC 9
//TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC,8);
#define OLED_RESET 4
Adafruit_SSD1306 tft(OLED_RESET);
#define VT_PIN A0 
#define AT_PIN A1
#define minus 5
#define plus  4 
#define fast  3 
//#define minuss 3 //PAS DE 10
//#define pluss  2  //PAS DE 10

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
int tempPin = A3;  //LM35
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
 //pinMode(pluss, INPUT); 
//pinMode(minuss, INPUT);
//digitalWrite(pluss, HIGH);
//digitalWrite(minuss, HIGH);
 pinMode(fast, INPUT); 
digitalWrite(fast, HIGH);
pinMode(10, OUTPUT);
h=EEPROM.read(100);
analogWrite(10, h);
 tft.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
 tft.display();
  tft.clearDisplay();
   tft.display();
   tft.setTextColor(WHITE);
 //tft.begin();
 //  tft.fillScreen();
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
    //pas de 10
    // if (digitalRead(pluss) == LOW)
if(!digitalRead(plus) && !digitalRead(fast))
    {



      
    h = h+10;
   
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


 //if (digitalRead(minuss) == LOW)
if(!digitalRead(minus) && !digitalRead(fast))
    {



      
    h = h-10;
   
     if (h < 0) {h=1;}
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
  tensiune = (sumatensiune * (5.0 / 1024.0) * 5.0)/.5;
 // voltage=tensiune
  current = (sumacurent * (5.1 / 1024.0))/0.22;
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
 // tft.setFont(&FreeSerif9pt7b);
  // tft.setTextSize(2);
  // tft.fillRect(0,0,95,35,BLACK);
// tft.setCursor(0,30);tft.setTextSize(2); tft.setTextColor(CYAN, BLACK); 
 
 // tft.fillScreen();
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.setTextColor(WHITE,BLACK );
  //tft.fillRect(0,0,95,35,BLACK);
 // tft.setTextColor(CYAN, BLACK); 
   //
  // tft.setCursor(20,0);
  tft.fillRect(0,0,64,15,BLACK);
   tft.print(tensiune);
   tft.setCursor(65,0);
    tft.setTextSize(2);tft.println("V");  tft.display();
 
 // else
 // tft.setCursor(0,30);tft.setTextSize(2); tft.setTextColor(CYAN, BLACK);tft.fillRect(0,0,128,35,BLACK); tft.print(voltage);
  
    
  // tft.setTextColor(YELLOW,BLACK); 
  // tft.fillRect(0,40,95,35,BLACK);
   tft.setCursor(0,18);tft.setTextSize(2);tft.setTextColor(WHITE,BLACK );
  tft.print(current);
  tft.setCursor(52,18);
  tft.setTextSize(2);
  tft.println("A");  
  
 // tft.setTextColor(WHITE,BLACK); 
 //tft.setTextColor(BLACK,WHITE);
  tft.setCursor(70,23);
  tft.setTextSize(1);
 // tft.setTextColor(WHITE,BLACK );
 tft.setTextColor(BLACK,WHITE);
 tft.fillRect(68,19,120,13,WHITE);
  //tft.setTextColor(BLACK,WHITE);
  //tft.fillRect(0,80,92,30,BLACK);
 tft.print(cel);
tft.setCursor(103,20);tft.setTextSize(1);
tft.println("o");
tft.setCursor(110,23);
//tft.setTextSize(1);
tft.println("C");
 //  tft.drawCircle(95, 85, 2);
   // tft.setFont();
   // tft.fillRect(0,115,128,15,BLACK);
   tft.setTextSize(2); //
   tft.fillRect(90,0,128,15,BLACK);
   //tft.display();
  // tft.setTextColor(YELLOW,BLACK);
   tft.setCursor(90,0);tft.setTextColor(WHITE,BLACK);
   tft.println(h);tft.display();
   //tft.setCursor(60,115);
  // tft.print("Pasi");
//delay(5000);


   if (cel > 40)
  {digitalWrite(6, HIGH); }
  
  
  if (cel < 35)
  digitalWrite(6, LOW);
  
  delay(500);
}

