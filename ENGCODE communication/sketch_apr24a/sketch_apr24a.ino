#include <LiquidCrystal.h>
#define MORSE_INPUT_PIN 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int contrast = 60;

const int DOT_DURATION = 100;
const int DASH_DURATION = 300;

const char* ENGCODE[] = {
  ".", "..", "...", "....", ".....", "......", ".......", "........", ".........", "..........", "...........", "............", ".............", "-", "--", "---", "----", "-----", "------", "-------", "--------", "---------", "----------", "-----------", "------------", "-------------",
};

void setup(){
  lcd.begin(16, 2);
  analogWrite(6, contrast);

  pinMode(MORSE_INPUT_PIN, INPUT);

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop(){
  int input = digitalRead(MORSE_INPUT_PIN);
  int count = -1;

  if (input == HIGH){
    String code = "";
      while(input == HIGH){
        delay(5);
        input = digitalRead(MORSE_INPUT_PIN);
        if(input == LOW){
          code += ".";
          delay(DOT_DURATION);

          lcd.setCursor(0, 1);
          lcd.print(".");
        }else{
          code += '-';
          delay(DASH_DURATION);

          lcd.setCursor(0, 1);
          lcd.print("-");
        }
        input = digitalRead(MORSE_INPUT_PIN);
      }

    for (int i = 0; i < 36; i++){
      if(strcmp(code.c_str(), ENGCODE[i]) == 0){
        char letter = 'A' + i;

        lcd.setCursor(0, 0);
        lcd.print(letter);

        break;
      }
    }
  }
}