#include <LiquidCrystal.h>
#include <Joystick.h>

class SpaceShip
{
public:
    SpaceShip()
    : y_position_(0)
    , y_onscreen_(-1)
    {}

    void init(LiquidCrystal & lcd)
    {
        // Define space ship.
        byte const space_ship_char[8] = {
            B00000,
            B01000,
            B11100,
            B01110,
            B11100,
            B01000,
            B00000,
        };
        // Register the space ship.
        lcd.createChar(custom_char_, space_ship_char);
    }

    void moveUp()
    {
        if (y_position_ == 1)
        {
            y_position_ = 0;
        }
    }

    void moveDown()
    {
        if (y_position_ == 0)
        {
            y_position_ = 1;
        }
    }

    void draw(LiquidCrystal & lcd)
    {
        // Proceed if the space ship should move.
        if (y_position_ != y_onscreen_)
        {
            // Erase the previous position of the space ship.
            // This is more efficient than clearing the entire
            // screen.
            lcd.setCursor(0, y_onscreen_);
            lcd.write(" ");

            // Draw the space ship in its new position.
            lcd.setCursor(0, y_position_);
            lcd.write(byte(custom_char_));

            // Update the ship's current position.
            y_onscreen_ = y_position_;
        }
    }

private:
    int y_position_;
    int y_onscreen_;

    int const custom_char_ = 0;
};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(0, 1, 13);
SpaceShip ship;

void setup()
{
    // Initialize the screen and joystick.
    joystick.begin();
    lcd.begin(2, 16);

    // Register the space ship.
    ship.init(lcd);
}

void loop()
{
    // Get the joystick's position.
    JoystickPosition position = joystick.position();

    // Convert the position to cursor dimensions.
    if (position.y > 0.75)
    {
        ship.moveDown();
    }
    else if (position.y < 0.25)
    {
        ship.moveUp();
    }

    ship.draw(lcd);
}
