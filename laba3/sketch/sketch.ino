#include <Arduino.h>
#include <EEPROM.h>
#include "keypad.h"
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define TIMEDELAY 5000

int rows[4] = {9,8,7,6};
int cols[4] = {5,4,3,2};

Keypad keyboard(rows, cols);

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

volatile bool choose=false;
volatile int new_menu=0;
int cur_menu = -1;

int mem_num;

void handle_interrupt()
{ 
  char chr = keyboard.get_key(); 
  switch(chr)
  {
  case 'A': 
  new_menu=cur_menu!=0?cur_menu-1:2; 
  break;
  case 'B': 
  new_menu=(cur_menu+1)%3; 
  break;
  case 'C': 
  choose = true;  
  break;
  default:
    break;
  }
}

void setup(){
  lcd.init();
  lcd.backlight();
  interrupts();
  EEPROM.get(0,mem_num); 
  attachInterrupt(digitalPinToInterrupt(cols[3]), handle_interrupt, FALLING);  
}

void print_menu(int cur_menu)
{
  switch(cur_menu)
  {
    case 0:
      lcd.print("Calculate");
      break;
    case 1:
      lcd.print("Memory: ");
      lcd.print(mem_num);
      break;
    case 2:
      lcd.print("Reset");
      break;
    default:
      break;
  }
}

int get_n(int col, int row, int max_len)
{
  int n = 0;  
  char chr = keyboard.get_key();
  int pos = col;
  lcd.setCursor(pos, row);
  while(pos<col+max_len&&chr!='#')
  {
    if(chr>='0'&&chr<='9')
    {
      n= n*10 + chr - '0';
      lcd.print(chr);
      pos++;
      lcd.setCursor(pos, row);
    }
    if(chr == '*')
    {
      n/=10;
      lcd.setCursor(pos,row);
      lcd.print(' ');
      lcd.setCursor(pos,row);
      pos--;
    }
    chr = keyboard.get_key();
  }
  
  return n;
}

void calc_menu()
{
  lcd.clear();
  int n1, n2;
    lcd.print("n1:from memory?");
    lcd.setCursor(0, 1);
    lcd.print("yes-A, no-B");
    char chr='\0';
    while(chr!= 'A' && chr != 'B')
    chr = keyboard.get_key();
    if(chr == 'A')
      {
          n1 = mem_num;
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("n1:"+String(n1));
      }
      else if(chr == 'B')
        { 
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("n1:");
          n1= get_n(4, 0, 10);
        }
    lcd.clear();
    lcd.print("n2:");
    n2 = get_n(4,0,10);
 
  int res = n1 & n2;
  lcd.clear();
  lcd.print("res: "+ String(res));
  lcd.setCursor(0, 1);
  lcd.print("sav?y-A,n-B");
  chr='\0';
  
  while(chr != 'A' && chr != 'B')
  chr = keyboard.get_key();
  delay(1000);
  if(chr == 'A')
  {
    mem_num = res;
    EEPROM.put(0, res);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Saved");
    delay(1000);
  }
}

void res_menu()
{ 
  lcd.clear();
  lcd.print("res?y-A,n-B");
  char chr='\0';
  
    while(chr != 'A' && chr != 'B')
      chr = keyboard.get_key();
    if(chr =='A')
    {
      mem_num = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Reseted");
      EEPROM.update(0, 0);
    }
  
  delay(2500);
}

void loop()
{
  if (new_menu != cur_menu)
  {
    detachInterrupt(digitalPinToInterrupt(cols[3]));
    lcd.setCursor(0,0);
    cur_menu=new_menu;
    lcd.clear();
    print_menu(cur_menu);
    attachInterrupt(digitalPinToInterrupt(cols[3]), handle_interrupt, FALLING);
  }
  else 
    if (choose)
    {
      detachInterrupt(digitalPinToInterrupt(cols[3]));
      switch (cur_menu)
      {
        case 0: 
        calc_menu();
        break;
        case 2:
        res_menu();
        break;
        default:
        break;
      }
      choose = false;
      lcd.clear();
      print_menu(cur_menu);
      attachInterrupt(digitalPinToInterrupt(cols[3]), handle_interrupt, FALLING);
    }
}
