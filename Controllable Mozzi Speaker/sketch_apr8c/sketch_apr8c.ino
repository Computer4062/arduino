#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos8192_int8.h>
#include <math.h>

#define CONTROL_RATE 64
#define potPin A0

Oscil <COS8192_NUM_CELLS, AUDIO_RATE> aCos(COS8192_DATA);
Oscil <COS8192_NUM_CELLS, AUDIO_RATE> aVibrato(COS8192_DATA);

const long intensityMax = 500;
int potValue = 0;

float mtof01(float midiNote) {
  float frequency = 440.0 * pow(2.0, (midiNote - 69) / 12.0);
  return round(frequency);
}

void setup(){
  potValue = analogRead(potPin);
  aCos.setFreq(mtof01(random(21, 80)));
  aVibrato.setFreq((float) map(potValue, 0, 1024, 0, intensityMax));
  startMozzi(CONTROL_RATE);
}

void loop(){ 
  updateControl();
  audioHook();
}

void updateControl(){
  potValue = analogRead(potPin);
}

int updateAudio(){
  long vibrato = map(potValue, 0, 1024, 0, intensityMax) * aVibrato.next();
  return (int)aCos.phMod(vibrato);
}