#define fan 9

int pwmValue = 128;

void setup(){
  Serial.begin(9600);

  pinMode(fan, OUTPUT);
}

void loop(){
  if (Serial.available()){
    String velocity = Serial.readString();
    pwmValue = atoi(velocity.c_str());
  }

  analogWrite(fan, pwmValue);
}