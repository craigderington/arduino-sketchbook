/*
  Measuring DC Voltage with Arduino 6-1-2016
*/

void setup() { 
 // init the serial comms
 Serial.begin(9600);  
}


void loop() {
  // read the input voltage
  int sensorValue = analogRead(A0);
  
  // convert the analog reading to a voltage
  float voltage = sensorValue * ( 5.0 / 1023.0 ) * 10;
  
  // print the value
  Serial.print("Voltage: ");
  
  Serial.print(voltage);
  
  Serial.print(" Volts\n");
  
  delay(1000);  
  
}
