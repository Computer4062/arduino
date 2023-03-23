import processing.serial.*;

Serial theSerialPort;
int[] serialBytesArray = new int[2];
int switchState;
int switchID;
int bytesCount = 0;
boolean init = false;
int fillColor = 40;

void setup(){
  size(500, 500);
  background(70);
  noStroke();
  
  println(Serial.list());
  
  String thePortName = Serial.list()[0];
  theSerialPort = new Serial(this, thePortName, 9600);
}

void draw(){
  fill(fillColor);
  ellipse(width /2 , height / 2, 230, 230);
}

void seriaEvent(Serial myPort){
  int inByte = myPort.read();
  
  if(init == false){
    if(inByte == 'Z'){
      myPort.clear();    
      init = true;  
      
      myPort.write('Z');
    } 
  }else{
    serialBytesArray[bytesCount] = inByte;
    bytesCount ++;
    
    if(bytesCount > 1){
      switchID = serialBytesArray[0];
      switchState = serialBytesArray[1];
      
      println(switchID + "\t" + switchState);
      
      if(switchState == 0) fillColor = 40;
      else fillColor = 255;
      
      myPort.write('Z');
      
      bytesCount = 0;
    }
  }
}
