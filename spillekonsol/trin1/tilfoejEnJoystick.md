# 2. trin: Tilføj en joystick


<img src="images/joystick.jpg" width="200">

## Board

![](images/board.png)

## Kode

Inden vi kan starte, skal 'Joystick' biblioteket installeres.
Download [Joystick.zip](../Joystick.zip) og installer biblioteket
i Arduino programmet

![](images/install_library.png)

Efter vi har installeret biblioteket kan vi begynde at undersøge hvordan vores joystick kan interagere med vores Arduino og ikke mindst vores LCD skærm som vi har tilsluttet. Joysticket har basalt set tre forskellige funktioner:
- Joysticket kan trykkes på toppen og virke som en knap. Knaptryk angives med en spænding på benet "SW" på joysticket og er koblet til en digital indgang på Arduinoen.  
- Joysticket kan rykkes til højre og venstre hvorved joysticket kan give en x-position mellem 0 og 1. Positionen angives som en spænding på benet "VRx" mellem 0 og 5 V.
- Joysticket kan rykkes op og ned hvorved joysticket kan give en y-position mellem 0 og 1. Positionen angives som en spænding på benet "VRy" mellem 0 og 5 V.

Med det følgende script kan vi få skrevet x og y-positionen af joysticket ud på LCD skærmen.
```C
#include <LiquidCrystal.h>
#include <Joystick.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Joystick joystick(0, 1, 13);

void setup()
{
    joystick.begin();
    lcd.begin(2, 16);
}

void loop()
{
    JoystickPosition position = joystick.position();

    lcd.setCursor(0, 0);
    lcd.print(position.x);

    lcd.setCursor(0, 1);
    lcd.print(position.y);
}
```
Joystickets tre funktioner kan kombineres. Så vi skubbe joysticket skråt til højre og op og samtidig trykke på det som en knap. Derved kan vi både angive en x og y-position samt et knap tryk. Prøve at rykke joysticket til de forskellige positioner og set hvordan tallene ændre sig på LCD skærmen. Hvad skal du gøre for at få angivet de følgende koordinater på skærmen ( x ,  y )?
- (0.0, 0.0) 
- (0.0, 1.0)
- (1.0, 0.0)
- (1.0, 1.0)
