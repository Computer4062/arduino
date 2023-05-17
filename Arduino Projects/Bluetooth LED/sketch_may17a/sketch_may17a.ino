#include <SoftwareSerial.h>

#define BT_RX 2
#define BT_TX 3

SoftwareSerial btSerial(BT_RX, BT_TX);

#define LED_PIN 13

void setup(){
  Serial.begin(9600);
  btSerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  if(btSerial.available()){
    char c = btSerial.read();
    if(c == 'C'){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
  }
}