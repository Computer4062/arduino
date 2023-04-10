import controlP5.*;
import processing.serial.*;

Serial port;

ControlP5 cp5;
PFont font;

boolean led1 = false;
boolean led2 = false;

void setup(){
  size(300, 400);
  
  printArray(Serial.list());
  
  port = new Serial(this, "COM5", 9600);
  
  cp5 = new ControlP5(this);
  font = createFont("calibri light", 20);
  
  cp5.addButton("green")
  .setPosition(100, 50)
  .setSize(100, 80)
  .setFont(font);
  ;
  
  cp5.addButton("yellow")
  .setPosition(100, 150)
  .setSize(100, 80)
  .setFont(font);
  ;
}

void draw(){
  background(255, 255 , 255);
  
  fill(0, 0, 0);
  textFont(font);
  text("LED REMOTE", width / 4, 30); 
}

void green(){
  if(led1 == false) led1 = true;
  else led1 = false;
  
  if (led1 == false) port.write('r');
  if(led1 == true) port.write('a');
}

void yellow(){
  if(led2 == false) led2 = true;
  else led2 = false;
  
  if (led2 == false)port.write('y');
  if (led2 == true) port.write('b');
 }
