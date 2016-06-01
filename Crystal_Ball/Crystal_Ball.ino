/*

  Crystal Ball

*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
 
  // set up the size of the lcd
  lcd.begin(16, 2);
  
  // set switch pin to input
  pinMode(switchPin, INPUT);
  
  // output "Ask the Crystal Ball" to the LCD
  lcd.print("Ask the...");
  
  // move the cursor down one line
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball");
  
}

void loop() {
  
  // read the switch pin - 6
  switchState = digitalRead(switchPin);
  
  if (switchState != prevSwitchState) {
   
     if (switchState == LOW) {
      
       reply = random(8);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("The crystal ball says...");
       lcd.setCursor(0, 1);
       
       // switch case for replies
       switch(reply) {
        
        case 0:
          lcd.print("YES!");
          break;
        case 1:
          lcd.print("Most likely");
          break;
        case 2:
          lcd.print("Certainly");
          break;
        case 3:
          lcd.print("Outlook good");
          break;
        case 4:
          lcd.print("Unsure");
          break;
        case 5:
          lcd.print("Ask again");
          break;
        case 6:
          lcd.print("Doubtful");
          break;
        case 7:
          lcd.print("No");
          break;         
       
       }     
     }  
  }
  
  // reset the switch state
  prevSwitchState = switchState;
  
}
