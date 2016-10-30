#include "Joystick.h"
#include "Arduino.h"

Joystick::Joystick(int x_pin, int y_pin, int button_pin)
: x_pin_(x_pin)
, y_pin_(y_pin)
, button_pin_(button_pin)
, rest_position_(0.5)
{}

void Joystick::begin()
{
    // Define the digital pin connected to the joystick's button pin
    // as an input.
    pinMode(button_pin_, INPUT);

    // Read and normalize the initial values of the joystick.
    rest_position_.x = normalize(analogRead(x_pin_));
    rest_position_.y = normalize(analogRead(y_pin_));
}

JoystickPosition Joystick::read() const
{
    // Initialize the position.
    JoystickPosition position;

    // Read and normalize the x value.
    // Read the value twice and use the 2nd one for reasons explained here:
    // https://www.quora.com/Why-is-a-little-delay-needed-after-analogRead-in-Arduino
    analogRead(x_pin_);
    position.x = normalize(analogRead(x_pin_));

    // Read and normalize the y value.
    analogRead(y_pin_);
    position.y = normalize(analogRead(y_pin_));

    return position;
}

JoystickPosition Joystick::position()
{
    // Get the 'raw' position of the joystick.
    JoystickPosition position = read();

    // Smoothen the raw position to get a value between 0 and 1 that
    // is at 0.5 when the joystick is in its resting position.
    position.x = smooth(position.x, rest_position_.x);
    position.y = smooth(position.y, rest_position_.y);

    return position;
}

bool Joystick::pressed() const
{
    int const value = digitalRead(button_pin_);
    return (value == LOW ? true : false);
}

float Joystick::smooth(float value, float rest)
{
    if (value <= rest)
    {
        return value / rest * 0.5;
    }
    else
    {
        return 0.5 + (value - rest) / (1.0 - rest) / 2.0;
    }

    return -1.0;
}

float Joystick::normalize(int value)
{
    return value / 1024.;
}

JoystickPosition::JoystickPosition(float initial)
: x(initial)
, y(initial)
{}
