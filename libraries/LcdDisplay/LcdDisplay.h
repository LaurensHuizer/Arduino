/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling LiquidCrystal LCD displays.
  It breaks a longer text into rows that fit on the display and every centers every row.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Simply print text to the display and the splitting into lines and centering of text is done
  automatically.
  
  Remark: Too long texts still fall off the screen, so still keep an eye on the length of the text!

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 6nd, 2015.
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

#ifndef LcdDisplay_h
#define LcdDisplay_h

#include "Arduino.h"
#include "LiquidCrystal.h"

class LcdDisplay
{
  public:
  LcdDisplay(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF);
  void *initialize(int screenWidth, int screenHeight);
  void print(char const *text);
  
  private:
  char *clone(char *a, int length);
  int getCenterStartPoint(char *text);
  int getSplitPoint(char *text);

  LiquidCrystal* lcd;
  short _screenWidth = 0;
  short _screenHeight = 0;
};

#endif