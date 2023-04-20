#include <SPI.h>
#include <Ethernet.h>
#include <SHA1.h>
#include <time.h>
#include <EEPROM.h>
#include <Twitter.h>

#define switchPin 2

int switchState = 0;
int lastSwitchState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

uint8_t mac[6] = {
  0xc4, 0x2c, 0x03, 0x0a, 0x3b, 0xb5
};
IPAddress ip {192, 168, 1, 43};
IPAddress gateway {192, 168, 1, 1};
IPAddress subnet (255, 255, 255, 0);

IPAddress twitter_ip (199, 59, 149, 232);
uint16_t twitter_port = 80;

unsigned long last_tweet = 0;
#define TWEET_DELTA (60L * 60L)

const static char consumer_key[] PROGMEM = "your_consumer_key_here";
const static char consumer_secret[] PROGMEM = "your_consumer_secret_here";
const static char access_token[] PROGMEM = "your_access_token_here";
const static char access_token_secret[] PROGMEM = "your_access_token_secret_here";

char buffer[512];
Twitter twitter(buffer, sizeof(buffer));

void setup(){
  Serial.begin(9600);
  Serial.println("Arduino and Twitter");

  pinMode(switchPin, INPUT);

  Ethernet.begin(mac, ip, gateway, subnet);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
    while (true) {}
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    while (true) {}
  }

  twitter.set_twitter_endpoint(PSTR("api.twitter.com"), 
    PSTR("/1.1/statuses/update.json"),
    twitter_ip, twitter_port, false);

  twitter.set_client_id(consumer_key, consumer_secret);

  twitter.set_account_id(access_token, access_token_secret);

  delay(500);
}

void loop(){
  if (twitter.is_read()){
    unsigned long now = twitter.get_time();
    if (last_tweet == 0) last_tweet = now - TWEET_DELTA + 15L;

    int readInput = digitalRead(switchPin);
    if (readInput != lastSwitchState){
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay){
      if (switchState != lastSwitchState) {
        lastSwitchState = switchState;
        switchState = readInput;
        if (switchState == HIGH){
          if (now > last_tweet + TWEET_DELTA){
            char msg[64];
            sprintf(msg, "Tweeting from #arduino by pushing a button is cool");

            Serial.print("Posting to Twitter: ");
            Serial.println(msg);

            last_tweet = now;

            if (twitter.post_status(msg)) Serial.println("Status updated");
            else Serial.println("Update failed");
          }
          else Serial.println("Wait a bit before pushing again...");
        }
      }
    }
  }
}