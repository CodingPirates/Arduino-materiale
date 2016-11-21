#include <LiquidCrystal.h>
#include <Joystick.h>

class Element
{
public:
    Element(int custom_char, int x, int y)
        : x_position_(x)
        , y_position_(y)
        , x_onscreen_(-1)
        , y_onscreen_(-1)
        , custom_char_(custom_char)
        {}

    int getX() const { return x_position_; }
    int getY() const { return y_position_; }

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

protected:
    int x_position_;
    int y_position_;
    int x_onscreen_;
    int y_onscreen_;
    int const custom_char_;
};

class SpaceShip : public Element
{
public:
    SpaceShip()
    : Element(0, 0, 0)
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

};


class Block : public Element
{
public:
    Block(int x, int y, int delay = 300)
    : Element(1, x, y)
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

    void stop()
    {
      x_position_ = -1;
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

private:
    int const delay_;
    int time_;
};


class Bullet : public Element
{
public:
    Bullet( int delay = 100)
    : Element(2, 16, 0)
    , delay_(delay)
    , time_(0)
    {}

    void init(LiquidCrystal & lcd)
    {
        // Define a block.
        byte const block_char[8] = {
            B00000,
            B00000,
            B00000,
            B00100,
            B00100,
            B00000,
            B00000,
            B00000,
        };
        // Register the block.
        lcd.createChar(custom_char_, block_char);

        time_ = millis();
    }
    
    void stop()
    {
      x_position_ = 16;
    }
    
    void shoot(int y)
    {
      if (x_position_ < 16) return;
      
      x_position_ = 1;
      y_position_ = y;
    }
    
    void move()
    {
        int new_time = millis();
        if (new_time - time_ > delay_)
        {
            time_ = new_time;
            if (x_position_ < 15)
            {
                ++x_position_;
            }
            else if (x_position_ == 15)
            {
                x_position_ = 16;
            }
        }
    }

private:
    int const delay_;
    int time_;
};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(0, 1, 13);
SpaceShip ship;
Block block(15, 0);
Bullet bullet;

void setup()
{
    // Initialize the screen and joystick.
    joystick.begin();
    lcd.begin(2, 16);

    // Register the space ship.
    ship.init(lcd);
    block.init(lcd);
    bullet.init(lcd);
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
    
    if (joystick.pressed())
    {
       bullet.shoot(ship.getY());
    }
    
    if ((bullet.getY() == block.getY()) && (bullet.getX() == block.getX()))
    {  
      bullet.stop();
      block.stop();
    }

    block.move();
    bullet.move();

    ship.draw(lcd);
    block.draw(lcd);
    bullet.draw(lcd);
}
