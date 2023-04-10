void setup(){
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  if (Serial.available()){
    char val = Serial.read();

    if (val == 'y') digitalWrite(10, HIGH);
    if (val == 'b') digitalWrite(10, LOW);
    if (val == 'r') digitalWrite(11, HIGH);
    if(val == 'a') digitalWrite(11, LOW);
  }
}