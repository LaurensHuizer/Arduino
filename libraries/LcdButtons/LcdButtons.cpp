/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for reading the 5 buttons of a LCD Keypad Shield - select, left, right, up, down - and
  responds to a press and the hold of a button by calling method.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Create an instance of this class and provide a 'buttonPress(int, bool)' method as parameter.
  This method will be called when a button is press or a button is held down for a longer time.
  See Example.ino how to use this class.

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

#define Released 0
#define VerifyPress 1
#define Pressed 2
#define HeldDown 3

#define None 0

#include "Arduino.h"
#include "LcdButtons.h"
#include "BaseTimedElement.h"

LcdButtons::LcdButtons(int pinButtons, void (*method)(int button, bool heldDown))
 : BaseTimedElement()
{
  _pinButtons = pinButtons;
  _buttonPress = method;
  _pressState = Released;
  _button = None;
  pinMode(pinButtons, INPUT);
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

void LcdButtons::update()
{
  int x = analogRead(_pinButtons);
  if (x < 60)
  {
    checkButtonPress(right);
  }
  else if (x < 200)
  {
    checkButtonPress(up);
  }
  else if (x < 400)
  {
    checkButtonPress(down);
  }
  else if (x < 600)
  {
    checkButtonPress(left);
  }
  else if (x < 800)
  {
    checkButtonPress(select);
  }
  else
  {
    _pressState = Released;
    _button = None;
    waitTimeStop();
  }
}


/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

void LcdButtons::checkButtonPress(short button)
{
  if (button != _button)
  {
    _pressState = VerifyPress;
    _button = button;
    setWaitTimeOnce(25);
    return;
  }
  if (waitTimePassed())
  {
    switch (_pressState)
    {
      case (VerifyPress):
        _buttonPress(button, false);
        _pressState = Pressed;
        setWaitTimeOnce(1000);
        break;
      case (Pressed):
      case (HeldDown):
        _buttonPress(button, true);
        _pressState = HeldDown;
        setWaitTimeOnce(400);
        break;
    }
  }
}