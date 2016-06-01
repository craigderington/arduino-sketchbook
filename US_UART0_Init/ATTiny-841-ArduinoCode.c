//#include <SoftwareSerial.h>;
unsigned long lastlooptime;
int pwmpin = 9;
int analogpin = 1;
//SoftwareSerial hetx(3,4);
void setup() {
  //set software serial to 1200 baud and clear looptimer
 // hetx.begin(1200);
  Serial.begin(9600);
  analogReference(EXTERNAL);
  lastlooptime = 0;
 }
void loop() {
 if (lastlooptime != 0 && millis()-lastlooptime < 3000)
    return; 
    //give system time to start
  delay(150);
  // set analog pin 0 to full power
   //analogWrite(0, 255);
   analogWrite(pwmpin,255);
   //wait for voltage to HE to settle
   delay(100);
   //setup 5 value array for read collection and averages
  int readings [5];
  int i;
  for (i=0; i<5; i++){readings [i] = analogRead(analogpin);}
  int sensorValue = (readings[0] + readings[1] + readings[2] + readings[3] + readings[4])/5;
  //Convert analog reading to voltage
   float voltage = sensorValue * (5.0 / 10.23);
   //turn off power to analog pin 0
   //analogWrite(0, 0);
   analogWrite(pwmpin,0);
   //define message to be transmitted, and start building format.
   char voltread[10];
  sprintf (voltread, "V;RB0%03i;",(int)voltage);
  ///Calculate XOR checksum for message
  byte checksum = 0;
    for(int i = 0; i < 9; i++) checksum ^= voltread[i];
    //define transmission string to be sent to radio and add checksum to message then transmit
 char transmission[13];
 sprintf (transmission, "%s%x;", voltread, checksum);
  //hetx.println(transmission);
  Serial.println (transmission);
  //wait 3 seconds a loop..this should not be reached in normal processing as power is only applied for 2.5 seconds
  lastlooptime=millis();
}