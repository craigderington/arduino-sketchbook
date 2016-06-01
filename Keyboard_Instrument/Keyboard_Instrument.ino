// set up an array of six elements
int buttons[6];

// create and define the notes arrary
int notes[] = {262, 294, 330, 349};

void setup() {
  buttons[0] = 2;
  Serial.begin(9600);
}


void loop() {
  int keyVal = analogRead(A0);
  Serial.println(keyVal);
  
  if(keyVal == 1023){
    tone(8, notes[0]);
  }
  else if(keyVal >= 990 && keyVal <= 1010){
    tone(8, notes[1]); 
  }
  else if(keyVal >= 505 && keyVal <= 515){
    tone(8, notes[2]); 
  }
  else if(keyVal >=5 && keyVal <= 10){
    tone(8, notes[3]); 
  }
  else{
    noTone(8); 
  }
}




