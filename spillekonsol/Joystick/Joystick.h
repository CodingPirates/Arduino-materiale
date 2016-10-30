/// Defines the position of a joystick using its
/// x and y coordinate.
struct JoystickPosition
{
    /// Initialize the joystick's position.
    JoystickPosition(float initial=0.0);

    float x;
    float y;
};

/// Simplified interface to joystick component.
class Joystick
{
public:
    /*!
    Initialize the joystick.

    \param x_pin : Analog pin connected to the VRx potentiometer.
    \param y_pin : Analog pin connected to the VRy potentiometer.
    \param button_pin : Digital pin connected to SW.
    */
    Joystick(int x_pin, int y_pin, int button_pin);

    /*!
    Determines the rest position of the joystick and defines
    the button as an input.
    */
    void begin();

    /// \return True when the button is being pressed.
    bool pressed() const;

    /*!
    Determines the current x and y coordinate of the joystick.

    The coordinates are defined between 0 and 1
    and set at 0.5 when at rest.

    \return The current position of the joystick.
    */
    JoystickPosition position();

private:
    /// \return The position of the joystick in the range [0, 1].
    JoystickPosition read() const;
    static float smooth(float value, float rest);
    static float normalize(int value);

    int const x_pin_;
    int const y_pin_;
    int const button_pin_;
    JoystickPosition rest_position_;
};
