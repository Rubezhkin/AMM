#pragma once
#include <Arduino.h>

class Keypad
{
  char symbols[4][4]{ '1','2','3','A','4', '5', '6', 'B', '7', '8', '9','C', '*', '0', '#', 'D'};
  int rows[4];
  int cols[4];

  public:
  Keypad(int rows[4], int cols[4])
  {
    for(int i=0; i<4;++i)
    {
      this->rows[i]=rows[i];
      this->cols[i]=cols[i];
      pinMode(this->rows[i], OUTPUT);
      digitalWrite(this->rows[i], LOW);
      pinMode(this->cols[i], INPUT_PULLUP);     
    }
  }
  char get_key()
  {
      for(int i=0; i<4;i++)
        digitalWrite(rows[i], HIGH);

      char res = '\0';
      for(int i=0; i<4&&res=='\0';i++)
      {
        digitalWrite(rows[i], LOW);
        delayMicroseconds(100);
        for(int j = 0; j<4&&res=='\0';j++)
          if(digitalRead(cols[j]) == LOW)
            {
              delay(200);
              if(digitalRead(cols[j]) == LOW)
                {
                  res = symbols[i][j];
                  delay(200);
                }
              while(digitalRead(cols[j]) == LOW){}
            }
        digitalWrite(rows[i], HIGH);
      }
      for(int i=0; i<4;i++)
        digitalWrite(rows[i], LOW);
      return res;
    
  }

};
