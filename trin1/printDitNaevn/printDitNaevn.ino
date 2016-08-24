// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup()
{
 // set up the LCD's number of columns and rows:
 // This particular 16x1 LCD is treated as an 8x2.  8 Characters by 2 rows.
 lcd.begin(8, 2);
 lcd.print("hello, world");
 }
 
void loop() {
lcd.setCursor(0,1);
lcd.print(millis() / 1000);
}
