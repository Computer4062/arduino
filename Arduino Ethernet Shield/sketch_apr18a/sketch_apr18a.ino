#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define switchPin 2
#define ledPin 13

int switchState = 0;
int lastSwitchState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;


byte mac [] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ipArduino {192, 168, 1, 123};
unsigned int ArduinoPort = 9999;

IPAddress ipComputer {192, 168, 1, 222};
unsigned int ComputerPort = 10000;

char packetBuffer[UPD_TX_PACKET_MAX_SIZE];
EthernetUDP UDP;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);

  Ethernet.begin(mac, ipArduino);
  UDP.begin(ArduinoPort);
}

void loop(){
  if (UDP.parsePacket()) UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

  if(packetBuffer == "Light") digitalWrite(ledPin, HIGH);
  else if(packetBuffer == "Dark") digitalWrite(ledPin, LOW);

  int readInput = digitalRead(switchPin);

  if(readInput != lastSwitchState)
    lastDebounceTime = millis();

  if ( (millis() - lastDebounceTime) > debounceDelay) 
    switchState = readInput;

  lastSwitchState = readInput;

  if(switchState == HIGH){
    Udp.beginPacket(ipComputer, ComputerPort);
    Udp.write("Pushed");
    Udp.endPacket();
  }else{
    Udp.beginPacket(ipComputer, ComputerPort);
    Udp.write("Released");
    Udp.endPacket();
  }

  delay(10);
  
}


















