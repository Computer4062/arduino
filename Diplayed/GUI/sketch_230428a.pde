import processing.serial.*;

Serial port;
String textValue = "";

void setup(){
  size(650, 200);
  textSize(20);
  
  port = new Serial(this, Serial.list()[0], 9600);
}

void draw(){
  background(255);
  
  stroke(0);
  fill(255);
  rect(50, 50, 550, 50);
  fill(0);
  textAlign(LEFT, TOP);
  
  text(textValue, 50, 70);
}

void keyPressed(){
  if(key == BACKSPACE && textValue.length() > 0){
    textValue = textValue.substring(0, textValue.length() - 1);
    port.write(textValue);
  }else if(key == ENTER && textValue.length() > 0){
    textValue = " ";
    port.write(textValue);
  }else{
    textValue += key;
    port.write(textValue);
  }
}
