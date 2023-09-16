#include <Arduino.h>
#include <TM1637Display.h>
#include <DHT.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
#define DHTPIN 4
#define DHTTYPE    DHT11 
#define MINUS_SG SEG_G

#define LIT_F SEG_A | SEG_F | SEG_G | SEG_E
#define LIT_H (SEG_F | SEG_G | SEG_B | SEG_E | SEG_C)
#define LIT_P SEG_E | SEG_F | SEG_A | SEG_B | SEG_G
#define O SEG_A | SEG_B | SEG_F | SEG_G 
#define LIT_SPACE 0

// The amount of time (in milliseconds) between tests

TM1637Display display(CLK, DIO);
DHT dht(DHTPIN, DHTTYPE);
uint8_t data[4];
void setup()
{
  display.setBrightness(0x0f);
  dht.begin();
  
  data[0] = O;
  data[1] = LIT_F;
  data[2] = LIT_P;
  data[3] = LIT_H;
}

void loop()
{
  display.clear();
  
  display.setSegments(data,2,2);
  float t = dht.readTemperature(true);
  display.showNumberDec(t,false,2);
  delay(2000);
  
  display.clear();
  
  display.setSegments(data + 2, 2, 2);
  float h = dht.readHumidity();
  display.showNumberDec(h,false,2);
  delay(2000); 
}
