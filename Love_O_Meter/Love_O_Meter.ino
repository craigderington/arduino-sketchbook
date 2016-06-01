// Love-O-Meter sketch
// define variables and constants

const int sensorPin = A0;
const float baselineTemp = 24.0;

// program setup
void setup(){
  Serial.begin(9600); // open a serial port connection
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW); 
  }
}

// program loop
void loop(){
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal); 
  
  // convert the ADC reading to a voltage
  float voltage = (sensorVal/1024.0) * 5.0;
  
  // print out the voltage
  Serial.print("  Voltage: ");
  Serial.print(voltage);
  
  // convert the voltage to temperature in degrees
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  
  // compare the temperature to the baseline temp
  if(temperature < baselineTemp) {
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   
  } else if(temperature >= baselineTemp + 2 &&
     temperature < baselineTemp + 4) {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW); 
        
  } else if(temperature >= baselineTemp + 4 &&
     temperature < baselineTemp + 6) {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        
  } else if(temperature >= baselineTemp + 6) {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);  
  }
  
  delay(1);
}
