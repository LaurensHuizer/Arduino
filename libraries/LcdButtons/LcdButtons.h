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

#ifndef LcdButtons_h
#define LcdButtons_h

#include "Arduino.h"
#include "BaseTimedElement.h"

class LcdButtons : public BaseTimedElement
{
  public:
    LcdButtons(int pinButtons, void (*method)(int button, bool heldDown));
    void update();
    
    static const short select = 1;
    static const short up = 2;
    static const short down = 3;
    static const short left = 4;
    static const short right = 5;
  private:
    void checkButtonPress(short button);

    //constructor variables
    int _pinButtons;

    //other variables
    short _button;
    short _pressState;
    void (*_buttonPress)(int button, bool heldDown);
};

#endif