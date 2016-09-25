#include "Keypad.h"

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
byte rowPins[rows] = {13, 12, 11, 10};

// Define column pins.
byte colPins[cols] = {9, 8, 7, 6};

// Initialize the keypad.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup()
{
    // Initialize a connection to the terminal.
    Serial.begin(9600);
}

void loop()
{
    // Retrieve a key.
    char key = keypad.getKey();

    // Verify if a key is pressed.
    if (key != NO_KEY)
    {
        // Print result to terminal.
        Serial.println(key);
    }
}
