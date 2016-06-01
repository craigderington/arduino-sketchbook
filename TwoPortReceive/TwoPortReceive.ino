/*

  SoftwareSerial test for multiple serial ports
  This example receives from two software serial ports and sends to the hardware serial port


*/

#include <SoftwareSerial.h>

// software serial on port 1

SoftwareSerial portOne(10, 11);

// software serial port 2

SoftwareSerial portTwo(8, 9);

void setup() {

  // open a serial connection and wait for ports to init
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial ports to connect
  }  
  
  // start each software serial port
  portOne.begin(9600);
  portTwo.begin(9600);
  
}


void loop() {
  
  // by default, the last init port is listening
  // when you want to listen on a port, explicitly select the port
  portOne.listen();
  Serial.println("Data from port one...");
  
  // while there is data coming in, read it and send it to the hardware serial port
  while (portOne.available() > 0) {
  
    char inByte = portOne.read();
    Serial.write(inByte);  
    
  }
  
  // new blank line to separate the data from the two ports
  Serial.println();
  
  // now listen on port 2
  portTwo.listen();
  Serial.println("Data from port two...");
  
  // while there is data coming from port two, read it and send it to the hardware serial
  while (portOne.available() > 0) {
  
     char inByte = portTwo.read();
     Serial.write(inByte); 
    
  }
  
  // new blank line to separare the two ports
  Serial.println();
  
}
