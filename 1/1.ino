#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests

TM1637Display display(CLK, DIO);

void setup()
{
}

void loop()
{
  display.setBrightness(0x0f);
  //1
task1();
//2
//task2();
//3
//task3();
   while(1);
}

void task1()
{
  int TEST_DELAY = 250;
  for(int i = 100; i >= -100; i-=2)
  {
  display.showNumberDec(i, false);
  delay(TEST_DELAY);
  }
  while(1);
}

void task2()
{
  int TEST_DELAY = 2000;
     for(int i = 100; i >=0; i-=10)
   {   
   display.clear();
   display.showNumberDec(i,true,3,1);
   delay(TEST_DELAY);
   }
   uint8_t minus = 0b01000000;
   uint8_t *ptr= &minus;
   display.setSegments(ptr,1);
   for(int i = 10; i <=100; i+=10)
   {    
   display.showNumberDec(i,true,3,1);
   delay(TEST_DELAY);
   }
}

void task3()
{
  int TEST_DELAY = 400;
  uint8_t text[] =
{
   0b00000110,
   0b00111111,
   0b00111001,
   0b01110110,
   0b00000000,
   0b00111111,
   0b01110011,
   0b01111001,
   0b00110111,
   0b00000000,
   0b00000110,
   0b00111111,
   0b00111001,
};
uint8_t* ptr = &text[0];
int i = 0;
while(1)
{
  display.setSegments(ptr+i);
  i = (i+1)%10;
  delay(TEST_DELAY);
}
}
