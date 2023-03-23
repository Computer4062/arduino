#define switchPin 2;

int switchState = 0;
int inByte = 0;

void setup(){
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  sayHello();
}

void loop(){
  if(Serial.available() > 0){
    inByte = Serial.read();
    switchState = digitRead(switchPin);

    Serial.write("0");
    Serial.write(switchState);
  }
}

void sayHello(){
  while(Serial.available() <= 0){
    Serial.print('Z');
    delay(200);
  }
}