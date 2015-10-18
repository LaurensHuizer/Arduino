/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling LiquidCrystal LCD displays.
  It breaks a longer text into rows that fit on the display and every centers every row.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  The LcdDisplay class uses LiquidCrystal.h for controlling the LCD display, so both LiquidCrystal and
  LcdDisplay have to be included in order to work.
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
  
// Both the LiquidCrystal and the LcdDisplay class must be referenced
#include <LiquidCrystal.h>
#include <LcdDisplay.h>

// Change the pin-numbers to match the connected pins from your Arduino board to the driverboard
LcdDisplay display(12, 11, 5, 4, 3, 2);

void setup() 
{
  // You have to initialize the display with the number of available characters in one row, and the number of rows
  display.initialize(16, 2);
  // Simply print a text to the display, it will automatically be split into multiple available rows and centered.
  display.print("This text is centered");
  // This will result in:
  //
  //     +1234567890123456+
  //     1  This text is  1
  //     2    centered    2
  //     +1234567890123456+
}

void loop() 
{
}