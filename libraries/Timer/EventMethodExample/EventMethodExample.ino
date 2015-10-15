/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for creating a timer to be used for timed actions, based on a timespan of milliseconds.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  When the timer is used on an event base, the timer calls a method when the set time is passed.
  Please keep in mind you either use the event methods OR the inline methods!
  
   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 5th, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/arduino/timer-library


  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

// Both the BaseTimedElement class and the Timer class must be referenced
#include <BaseTimedElement.h>
#include <Timer.h>

Timer timer;
bool blink = false; // Demo variable, to blink the led on pin 13

// This method is being called when the timer ticks.
// For this example we blink the led from pin 13
void onTimer()
{
  blink = !blink;
  digitalWrite(13, blink ? HIGH : LOW);
}

void setup()
{
  pinMode(13, OUTPUT);
  //Every 200 milliseconds call the onTimer method
  //You can also use After(ms, void (*method)()) for a non-recurring timer
  timer.every(200, &onTimer);
}

void loop()
{
  // This function is required to be called in the loop in order for the timer to work!
  timer.update();
}