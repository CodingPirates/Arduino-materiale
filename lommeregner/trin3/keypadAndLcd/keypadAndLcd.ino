#include <LiquidCrystal.h>
#include "Keypad.h"

// Initialize the screen.
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

// Define dimensions.
const byte rows = 4;
const byte cols = 4;

// Define string for each key.
char keys[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Define row pins.
byte rowPins[rows] = {13,12,11,10};

// Define column pins.
byte colPins[cols] = {9,8,7,6};

// Initialize the keypad.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup()
{
    lcd.begin(8, 2);
}

// Keep track of the number of characters
// printed on each line.
int countLine1 = 0;
int countLine2 = 0;

void loop()
{
    // Retrieve a key.
    char key = keypad.getKey();

    // Verify if a key is pressed.
    if (key != NO_KEY)
    {
        // Clear the screen and reset the counters
        // when the screen is full.
        if (countLine1 == 16 && countLine2 == 16)
        {
            lcd.clear();
            countLine1 = 0;
            countLine2 = 0;
        }

        // Print the key to the screen.
        lcd.print(key);

        if (countLine1 < 16)
        {
            // Increment the counter when the key
            // was printed on line 1.
            countLine1 += 1;

            // Prepare to print on the 2nd line
            // when the 1st line is full.
            if (countLine1 == 16)
            {
                lcd.setCursor(0, 1);
            }
        }
        else if (countLine2 < 16)
        {
            // Increment the counter when the key
            // was printed on line 2.
            countLine2 += 1;

            // Prepare to print on the 1st line
            // when the 2nd line is full.
            if (countLine2 == 16)
            {
                lcd.setCursor(0, 0);
            }
        }
    }
}
