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


class Block
{
public:
    Block(int x, int y, int delay = 300)
    : x_position_(x)
    , y_position_(y)
    , x_onscreen_(-1)
    , y_onscreen_(-1)
    , delay_(delay)
    , time_(0)
    {}

    void init(LiquidCrystal & lcd)
    {
        // Define a block.
        byte const block_char[8] = {
            B11111,
            B11111,
            B11111,
            B11111,
            B11111,
            B11111,
            B11111,
            B11111,
        };
        // Register the block.
        lcd.createChar(custom_char_, block_char);

        time_ = millis();
    }

    void move()
    {
        int new_time = millis();
        if (new_time - time_ > delay_)
        {
            time_ = new_time;
            if (x_position_ > 1)
            {
                --x_position_;
            }
            else if (x_position_ == 1)
            {
                x_position_ = -1;
            }
        }
    }

    void draw(LiquidCrystal & lcd)
    {
        // Proceed if the block should move.
        if ((x_position_ != x_onscreen_) || (y_position_ != y_onscreen_))
        {
            // Erase the previous position of the block.
            // This is more efficient than clearing the entire
            // screen.
            lcd.setCursor(x_onscreen_, y_onscreen_);
            lcd.write(" ");

            // Draw the block in its new position when it
            // will be visible.
            if ((x_position_ >= 0) && (x_position_ <= 15) &&
                (y_position_ >= 0) && (y_position_ <= 1))
            {
                lcd.setCursor(x_position_, y_position_);
                lcd.write(byte(custom_char_));
            }

            // Update the ship's current position.
            x_onscreen_ = x_position_;
            y_onscreen_ = y_position_;
        }
    }

private:
    int x_position_;
    int y_position_;
    int x_onscreen_;
    int y_onscreen_;
    int const delay_;
    int time_;

    int const custom_char_ = 1;
};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(0, 1, 13);
SpaceShip ship;
Block block(15, 0);

void setup()
{
    // Initialize the screen and joystick.
    joystick.begin();
    lcd.begin(2, 16);

    // Register the space ship.
    ship.init(lcd);
    block.init(lcd);
}

int count = 0;

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

    block.move();

    ship.draw(lcd);
    block.draw(lcd);
}
