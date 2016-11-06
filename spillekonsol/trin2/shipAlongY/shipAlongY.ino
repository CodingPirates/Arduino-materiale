#include <LiquidCrystal.h>
#include <Joystick.h>

// Define space ship.
byte spaceShip[8] = {
    B00000,
    B01000,
    B11100,
    B01110,
    B11100,
    B01000,
    B00000,
};


LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(0, 1, 13);

// Keep track of the x position of the space ship.
int ship_y_position = 0;

void setup()
{
    // Register the space ship.
    lcd.createChar(0, spaceShip);

    // Initialize the screen and joystick.
    joystick.begin();
    lcd.begin(2, 16);
}

void loop()
{
    // Get the joystick's position.
    JoystickPosition position = joystick.position();

    // Convert the position to cursor dimensions.
    int new_ship_y_position = ship_y_position;
    if (ship_y_position == 0 && position.y > 0.75)
    {
        new_ship_y_position = 1;
    }
    else if (ship_y_position == 1 && position.y < 0.25)
    {
        new_ship_y_position = 0;
    }

    // Proceed if the space ship should move.
    if (new_ship_y_position != ship_y_position)
    {
        // Erase the previous position of the space ship.
        // This is more efficient than clearing the entire
        // screen.
        lcd.setCursor(0, ship_y_position);
        lcd.write(" ");

        // Draw the space ship in its new position.
        lcd.setCursor(0, new_ship_y_position);
        lcd.write(byte(0));

        // Update the ship's current position.
        ship_y_position = new_ship_y_position;
    }
}
