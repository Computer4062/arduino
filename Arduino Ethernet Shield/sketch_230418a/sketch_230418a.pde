import hypermedia.net.*;

UDP udp;
String currentMessage;

String ip = "192.168.1.123";
int port = 9999;

void setup(){
  size(700, 700);
  noStroke();
  fill(0);
  
  udp = new UDP(this, 10000);
  udp.listen(true);
}

void draw(){
  ellipse(width / 2, height / 2, 230, 230);
}

void receive(byte[] data){
  if(data.length == 6 || data.length == 8){
    for(int i = 0; i < data.length; i++)
      currentMessage += data[i];
      
     if(currentMessage == "Pushed"){
       udp.send("Light", ip, port);
       fill(255);
     }else if (currentMessage == "Released"){
       udp.send("Dark", ip, port);
       fill(0);
     }
     
  }  
}
