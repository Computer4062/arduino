#include "SPI.h"
#include "SD.h"
#include "TMRpcm.h"

#define SD_CSpin 2
TMRpcm tmrpcm;

void setup(){
  tmrpcm.speakerPin = 9;
  if(!SD.begin(SD_CSpin)) return; 

  tmrpcm.setVolume(5);
  tmrpcm.play("1.wav");
}

void loop(){

}