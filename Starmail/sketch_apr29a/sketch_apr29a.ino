#define switchPin 2

void setup(){
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  int input = digitalRead(switchPin);
  if(Serial.available()){
    if(input == HIGH){
      Serial.write('w');
    }
  }
}