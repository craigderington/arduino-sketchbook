/*
  AC Voltage Measurement 6-1-2016
*/

void setup() {
  
  // init the serial communications
  Serial.begin(9600);    
  
}


void loop() {
  
  // read the sensor value
  int sensorValue = analogRead(A0);
  
  // convert the analog reading
  float voltage = sensorValue * (255.0 / 1023.0 );
  
  // print the voltage reading out the the serial monitor
  Serial.print("AC Voltage: ");
  
  Serial.print(voltage);
  
  Serial.println(" Volts");
  
  // trigger short delay between readings
  delay(1000);  
  
}


