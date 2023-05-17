#include <SoftwareSerial.h>

#define BT_RX 2
#define BT_TX 3

SoftwareSerial btSerial(BT_RX, BT_TX);

void setup(){
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop(){
  if(btSerial.available()){
    char c = btSerial.read();
    Serial.write(c);
  }

  if(Serial.available()){
    char c = Serial.read();
    btSerial.write(c);
  }
}