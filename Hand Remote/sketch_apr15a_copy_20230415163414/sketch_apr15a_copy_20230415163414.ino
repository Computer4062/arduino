void setup(){
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop(){
  if (Serial.available()){
    char value = Serial.read();

    if(value == 'a') digitalWrite(2, HIGH);
    if(value == 'b') digitalWrite(3, HIGH);
    if(value == 'c') {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
    }
  }
}