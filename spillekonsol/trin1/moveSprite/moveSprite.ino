#include <LiquidCrystal.h>
#include <Joystick.h>

// Define space ship.
byte spaceShip[8] = {
    B00000,
    B00000,
    B00000,
    B00100,
    B01110,
    B11111,
    B01010
};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(1, 0, 13);

void setup()
{
    // Register the space ship.
    lcd.createChar(0, spaceShip);

    // Initialize the screen and joystick.
    joystick.begin();
    lcd.begin(2, 16);
}

// Keep track of the x position of the space ship.
int x_position = 8;

void loop()
{
    // Get the joystick's position.
    JoystickPosition position = joystick.position();

    // Convert the position to cursor dimensions.
    int new_x_position = int(position.x * 16);

    // Proceed if the space ship should move.
    if (new_x_position != x_position)
    {
        // Erase the previous position of the space ship.
        // This is more efficient than clearing the entire
        // screen.
        lcd.setCursor(x_position, 1);
        lcd.write(" ");

        // Draw the space ship in its new position.
        lcd.setCursor(new_x_position, 1);
        lcd.write(byte(0));

        // Update the ship's current position.
        x_position = new_x_position;
    }
}
