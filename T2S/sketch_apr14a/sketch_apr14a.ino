#include <LiquidCrystal.h>
#include <SD.h>
#include <SPI.h>

int contrast = 60;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String content = " ";

void setup(){
  Serial.begin(9600);

  analogWrite(6, contrast);
  lcd.begin(16, 2);
  
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop(){
  if(Serial.available()) content = Serial.readString();

  int length = content.length();

  if (length > 16){
    String text_1 = content.substring(0, 16);
    String text_2 = content.substring(17, content.length());

    lcd.setCursor(0, 0);
    lcd.print(text_1);
    
    lcd.setCursor(0, 1);
    lcd.print(text_2);

  }else if(length <= 16){
    lcd.setCursor(0, 0);
    lcd.print(content);
  }
  
  delay(1000);
}