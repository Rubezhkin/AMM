#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
#define MINUS_SG SEG_G
#define LIT_A SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_G
#define LIT_B SEG_F | SEG_E | SEG_D | SEG_C | SEG_G
#define LIT_C SEG_D | SEG_E | SEG_F | SEG_A
#define LIT_D SEG_G | SEG_E | SEG_D | SEG_C | SEG_B
#define LIT_E SEG_A | SEG_F | SEG_G | SEG_E | SEG_D
#define LIT_F SEG_A | SEG_F | SEG_G | SEG_E
#define LIT_G SEG_A | SEG_F | SEG_E | SEG_D | SEG_C
#define LIT_H (SEG_F | SEG_G | SEG_B | SEG_E | SEG_C)
#define LIT_I SEG_F | SEG_E
#define LIT_J SEG_D | SEG_C | SEG_B
#define LIT_L SEG_F | SEG_E | SEG_D
#define LIT_N SEG_E | SEG_G | SEG_C
#define LIT_O SEG_E | SEG_G | SEG_C | SEG_D
#define LIT_P SEG_E | SEG_F | SEG_A | SEG_B | SEG_G
#define LIT_Q SEG_F | SEG_A | SEG_B | SEG_G | SEG_C
#define LIT_R SEG_E | SEG_G
#define LIT_T SEG_F | SEG_G | SEG_E | SEG_D
#define LIT_U SEG_F | SEG_E | SEG_D | SEG_C | SEG_B
#define LIT_Y SEG_F | SEG_G | SEG_B | SEG_C | SEG_D
#define LIT_SPACE 0

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
task2();
//3
task3();
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
 
}

void task2()
{
  int TEST_DELAY = 2000;
     for(int i = 100; i >=-100; i-=10)
   {   
   display.clear();
   uint8_t minus = MINUS_SG;
   uint8_t *ptr= &minus;
   if(i < 0)
   display.setSegments(ptr);
   display.showNumberDecEx(abs(i),0xff,true,3,1);
   delay(TEST_DELAY);
   }
 
}

void task3()
{
  int TEST_DELAY = 400;
  uint8_t text[] =
{
   LIT_L,
   LIT_O,
   LIT_C,
   LIT_H,
   LIT_SPACE,
   LIT_O,
   LIT_P,
   LIT_E,
   LIT_N,
   LIT_SPACE,
   LIT_SPACE,
   LIT_SPACE,
   LIT_SPACE,
   LIT_L,
   LIT_O,
   LIT_C,
};
uint8_t* ptr = &text[0];
int i = 0;
while(1)
{
  display.setSegments(ptr+i);
  i = (i+1)%(sizeof(text)/sizeof(text[0])-3);
  delay(TEST_DELAY);
}
}
