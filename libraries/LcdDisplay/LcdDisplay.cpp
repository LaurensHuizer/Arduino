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

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "LcdDisplay.h"

LcdDisplay::LcdDisplay(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF)
{
  lcd = new LiquidCrystal(pinA, pinB, pinC, pinD, pinE, pinF);
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

void *LcdDisplay::initialize(int screenWidth, int screenHeight)
{
  lcd->begin(screenWidth, screenHeight);
  _screenHeight = screenHeight;
  _screenWidth = screenWidth;
}

void LcdDisplay::print(char const *text)
{
  lcd->clear();

  if (_screenWidth == 0 || _screenHeight == 0)
  {
    lcd->setCursor(0, 0);
    lcd->print("Use Initialize()");
    return; //No CenterText; width unknown
  }
    
  int row = 0;
  char *currentText = (char *)&text[0];
  int textLength = strlen(currentText);
  
  while (textLength > 0 && row < _screenWidth)
  {
    int splitPoint = getSplitPoint(currentText);
    char *lineText = clone(currentText, splitPoint);
    lcd->setCursor(getCenterStartPoint(lineText), row);
    lcd->print(lineText);
    delete(lineText);
    
    if (splitPoint < textLength)
    {
      currentText = &currentText[splitPoint + 1];
      textLength = strlen(currentText);
    }
    else
    {
      textLength = 0;
    }
    row++;
  }
  char *rowText;  
}


/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

char *LcdDisplay::clone(char *a, int length)
{
  char *b = new char[length + 1];
  if (length > 0)
  {
    for (int i = 0; i < length; i++)
    {
      b[i]=a[i];
    }
  }
  b[length] = '\0';
  return b;
}

int LcdDisplay::getCenterStartPoint(char *text)
{
  int textLength = strlen(text);
  return (int)((_screenWidth - textLength)/2);
}

int LcdDisplay::getSplitPoint(char *text)
{
  int textLength = strlen(text);
  if (textLength <= _screenWidth)
    return textLength;

  int i = _screenWidth;
  while (text[i] != ' ' && i > 0)
  {
    i--;
  }

  return i == 0 ? _screenWidth : i;
}