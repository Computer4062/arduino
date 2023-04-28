#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int contrast = 60;

String text = "";

void setup(){
  analogWrite(6, contrast);
  lcd.begin(16, 2);

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  Serial.begin(9600);
}

void loop(){
  if(Serial.available())
    text = Serial.readString();

  lcd.setCursor(0, 0);
  lcd.print(text);
  lcd.scrollDisplayLeft();

  delay(300);
}