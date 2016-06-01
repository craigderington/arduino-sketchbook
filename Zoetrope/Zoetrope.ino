const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStatePin = 5;
const int potPin = A0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
 
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchState, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
 
  digitalWrite(enablePin, LOW); 
  Serial.begin(9600);
}

void loop() {
  
  // read sensors
  onOffSwitchState = digitalRead(onOffSwitchStatePin);
  
  // short delay
  delay(10);
  
  directionSwitchState = digitalRead(directionSwitchPin);
  
  // read motor state
  motorSpeed = analogRead(potPin) / 4;
  Serial.println(motorSpeed);
  
  // read motor state
  if (onOffSwitchState != previousOnOffSwitchState) {
    
   if (onOffSwitchState == HIGH) {
     
     motorEnabled = !motorEnabled;
     Serial.println("Changing motor power state...");
   } 
    
  }
  
  // read direction switch state  
  if (directionSwitchState != previousDirectionSwitchState) {
   
   if (directionSwitchState == HIGH) {
     
     motorDirection = !motorDirection;
     Serial.println("Reversing motor direction...");
    
   } 
    
  }
  
  // set H-Bridge direction
  if (motorDirection == 1) {
  
     digitalWrite(controlPin1, HIGH);
     digitalWrite(controlPin2, LOW); 
    
  }
  
  else {
     
     digitalWrite(controlPin1, LOW);
     digitalWrite(controlPin2, HIGH); 
    
  }
  
  // set power
  if (motorEnabled == 1) {
   
     analogWrite(enablePin, motorSpeed); 
    
  }
  
  else {
   
     analogWrite(enablePin, 0); 
    
  }
  
  // preserve the switch state for next run
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
  
}




