/*

  LED Bargraph Display
  6-1-2016
  Craig Derington

*/


// define connections for the lcd
const int data = 6;
const int clock = 7;
const int latch = 5;
const int led0 = 3;
const int led1 = 4;

void setup() {

  // init the digital pins as output
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
 
  AnimateDisplay(); 
  
}


void loop() {
  
  // read the analog port
  int voltage = analogRead(A0);
  
  // scaling of 0 to 5V (0 - 1023)
  voltage = voltage / 102;
  DisplayBar(voltage - 2);
  
  // control the bottom two leds
  if (voltage > 0)
  {
    digitalWrite(led0, HIGH);
  } 
  else {
    digitalWrite(led0, LOW); 
  }
  if (voltage > 1)
  {
    digitalWrite(led1, HIGH);
  } 
  else {
    digitalWrite(led1, LOW);
  }
  // short delay
  delay(200);  
}

void DisplayBar(char d)
{
   // define iterator
   int i;
   digitalWrite(data, HIGH);
  
   for (i=0; i < d; i++)
   {
      digitalWrite(clock, LOW);
      delay(1);
      digitalWrite(clock, HIGH);
      delay(1);
   }
   
   digitalWrite(data, LOW);
   for (i=0; i < 8; i++)
   {
     digitalWrite(clock, LOW);
     delay(1);
     digitalWrite(clock, HIGH);
     delay(1);
   }
   
   // latch the data
   digitalWrite(latch, LOW);
   delay(10);
   digitalWrite(latch, HIGH);
  
}

void AnimateDisplay()
{
   // define iterator
   int i;
   
   // bar graph goes upwards
   digitalWrite(led0, HIGH);
   delay(100);
   digitalWrite(led1, HIGH);
   delay(100);
   
   // display rising bargraph
   for (i = 1; i < 9; i++)
   {
     DisplayBar(i);
     delay(100);
   }
   
   // bar graph goes downwards
   for (i = 8; i >= 0; i--)
   {
     DisplayBar(i);
     delay(100);
   }
  
   // turn off the two leds
   
   digitalWrite(led1, LOW);
   delay(100);
   digitalWrite(led0, LOW);
   delay(100);
}
