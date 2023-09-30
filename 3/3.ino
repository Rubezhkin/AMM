#include <LiquidCrystal_I2C.h>
//пока только интерфейс сделан
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

enum class Status
{
  MENU_1,
  MENU_2,
  MENU_3,
  SET_NUM_1,
  SET_NUM_2,
  RESULT_SAVE,
  RESET_CONFIRM
};

Status status = Status::MENU_1;

void getStatus(Status status)
{
   switch(status)
  {
    case Status::MENU_1:
      lcd.print("1) Calculate");
      break;
     case Status::MENU_2:
      lcd.print("2) Memory");
      break;
     case Status::MENU_3:
      lcd.print("3) Reset");
      break;
     case Status::SET_NUM_1:
      lcd.print("Enter 1 num: ");
      break;
     case Status::SET_NUM_2:
      lcd.print("Enter 2 num: ");
      break;
     case Status::RESULT_SAVE:
      lcd.print("Result: ");
      lcd.setCursor(0,1);
      lcd.print("Save? A-Y, B-N");
      break;
     case Status::RESET_CONFIRM:
      lcd.print("Reset?");
      lcd.setCursor(0,1);
      lcd.print("A-Yes, B-No");
      break;
  }
}

void setup() {
  lcd.init();
  lcd.backlight();

  
}

void loop() {
  while(1)
  {
    getStatus(status);
    delay(2000);
    lcd.clear();
    status = (Status)(((int)status+1)%7);
  }
}
