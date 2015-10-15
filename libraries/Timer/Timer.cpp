/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for creating a timer to be used for timed actions, based on a timespan of milliseconds.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  A timer could be used in two different ways, but not in mixed mode. So you have to choose between:
  
  - Event mode
    Use after(int ms, void (*method)()) or every(int ms, void (*method)()) in combination with update()
    See EventMethodExample.ino how to use the timer this way.
  
  - Inline mode
    Use setWaitTime(int ms) in combination with passed().
    See InlineExample.ino how to use the timer this way.

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

#include "Arduino.h"
#include "Timer.h"
#include "BaseTimedElement.h"

Timer::Timer()
 : BaseTimedElement()
{ }

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

//Inline timer where the Passed() is called every cycle
void Timer::setWaitTime(int ms)
{
  setWaitTimeOnce(ms);
}

bool Timer::passed()
{
  return waitTimePassed();
}

//Event timer where Update() is called every cycle, invokes method
void Timer::after(int ms, void (*method)())
{
  setWaitTimeOnce(ms);
  _callbackMethod = method;
}

void Timer::every(int ms, void (*method)())
{
  setWaitTimeEvery(ms);
  _callbackMethod = method;
}

void Timer::update()
{
  if (_callbackMethod && waitTimePassed())
  {
    _callbackMethod();
  }
}

void Timer::stop()
{
  waitTimeStop();
}