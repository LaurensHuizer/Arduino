/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for reading the 5 buttons of a LCD Keypad Shield - select, left, right, up, down - and
  responds to a press and the hold of a button by calling method.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  The buttons of a LCD Keypad Shield sometimes gave false positives, and we wanted to have 
  functionality to read if the button was pressed or held down for a longer period of time.

  This class provides a stable way to check if a button was really pressed or held.
  
   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 3rd, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/arduino/lcd-keypad-shield
  

  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

// Both the BaseTimedElement class and the LcdButtons class must be referenced
#include <BaseTimedElement.h>
#include <LcdButtons.h>

// Change the pin-numbers to match the connected pin from your Arduino board to the shield
// This has to be an analogue pin!
LcdButtons buttons(A0, &buttonPress);

// Demo method that is called when the button is pressed or held
void buttonPress(int button, bool heldDown)
{
  // The class has five constants for buttons:
  // Select, Up, Down, Left and Right
  switch (button)
  {
    case LcdButtons::select:
      Serial.print("select");
      break;
    case LcdButtons::up:
      Serial.print("up");
      // You can simply check if the button is held down for a longer period,
      // and do a different action based upon that
      if (heldDown)
        digitalWrite(13, HIGH);
      break;
    case LcdButtons::down:
      Serial.print("down");
      if (heldDown)
        digitalWrite(13, LOW);
      break;
    case LcdButtons::left:
      Serial.print("left");
      break;
    case LcdButtons::right:
      Serial.print("right");
      break;
  }
  if (heldDown)
    Serial.print(" (button held down)");
  Serial.println("");
}

void setup()
{
  // We are going to print button press events to serial. To see them open the Serial monitor
  Serial.begin(9600);
  // We set pin 13 (the led on your Arduino) on when you hold the up button and off when you hold the down button
  pinMode(13, OUTPUT);
}

void loop()
{
  // This function is required to be called in the loop in order for the buttons to work!
  buttons.update();
}