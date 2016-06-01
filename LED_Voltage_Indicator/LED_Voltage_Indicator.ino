/*

  Led Voltage Level Indicator
  6-1-2016

*/


const int led = 13;
const int voltageIn = A0;

void setup() {
 
 // init pin 13 as output
 pinMode(led, OUTPUT); 
  
}


void loop() {
 
  // read the voltage from analog port 
  double voltage = analogRead(A0);
 
  // calculate the voltage
  voltage = (5.0/1023.0) * voltage;
 
 if (voltage < 0.5)
 {
   // set the value low
   digitalWrite(led, LOW);   
 }
 
 if (voltage >= 0.5)
 {
    // set the value high, then delay, then low
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);    
 }
 
 if (voltage >= 3.3) && (voltage < 4.0)
 {
    // set the value high, then low
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);    
 }
 
 if (voltage >= 4.0)
 {
   // set the value high
   digitalWrite(led, HIGH);   
 }  
}
