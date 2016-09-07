const int buttonPin = 12;
const int ledPin =  13;

void setup()
{
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}

void loop()
{
    // read the state of the pushbutton value:
    int buttonState = digitalRead(buttonPin);
  
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) 
    {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        // turn LED off:
        digitalWrite(ledPin, LOW);
    }
}
