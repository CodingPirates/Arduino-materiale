#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
 
const int buttonPin = 12;

int counter = 0;
bool buttonPressed = false;

void setup()
{
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("test");
 
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
 }
 
void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // Only increase the counter when
    // the button is pressed initially.
    if (!buttonPressed) {
     counter += 1;
    }
    // Mark the button as pressed
    buttonPressed = true;
  }
  else {
    // Mark the button as released.
    buttonPressed = false;
  }
 
 // Print the current value of the counter.
 lcd.setCursor(0,1);
 lcd.print(counter);
}
