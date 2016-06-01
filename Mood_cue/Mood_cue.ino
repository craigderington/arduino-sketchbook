// import servi library
#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int angle;

// prigram setup
void setup() {

  // attach the servo on PWM pin 9
  myServo.attach(9);
  
  // open up a serial connection
  Serial.begin(9600);

}

// program loop
void loop() {
 
 potVal = analogRead(potPin);
 Serial.print("potVal: ");
 Serial.print(potVal);
 
 angle = map(potVal, 0, 1023, 0, 179);
 Serial.print(", angle: ");
 Serial.println(angle);
 
 myServo.write(angle);
 delay(10000);
  
}
