/*

  Software serial multiple serial test

  The circuit:
  * RX is digital pin 10
  * TX is digital pin 11

*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup() {
  
   // open a serial connection and wait for ports to initialize
   Serial.begin(57600);
   while (!Serial) {     
    ; // wait for serial ports to connect     
   }
   
   Serial.println("Goodnight Saigon");
   
   // set the data rate for the Software Serial port
   mySerial.begin(4800);
   mySerial.println("Hello World!");
  
}

void loop() {
  
  if (mySerial.available()) {
    
    Serial.write(mySerial.read());
   
  } 
  
  if (Serial.available()) {
  
    mySerial.write(Serial.read());
   
  }
  
}
