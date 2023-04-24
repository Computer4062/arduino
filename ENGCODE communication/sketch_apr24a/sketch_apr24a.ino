#include <LiquidCrystal.h>
#define MORSE_INPUT_PIN 2

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
      }else{
        code += '-';
        delay(DASH_DURATION);
      }
    }

    for (int i = 0; i < 36; i++){
      if(strcmp(code.c_str(), ENGCODE[i]) == 0){
        char letter = 'A' + i;
        count += 1;

        lcd.setCursor(count, 0);
        lcd.print(letter);

        break;
      }
    }
  }
}
