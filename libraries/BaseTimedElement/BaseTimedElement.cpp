/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This base class is for elements that have timed actions, based on a timespan of milliseconds.
  Provides functionality to set a timer in milliseconds and to check if the time is passed.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Set either a single wait time (setWaitTimeOnce(ms)) or a reoccurring wait time (setWaitTimeEvery(ms))
  Check in the loop if the waitTimePassed() is true.
  You can only set one wait time at the time
  setWaitTimeEvery will automatically set a new wait time
  
   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 2nd, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/blog/arduino


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
#include "BaseTimedElement.h"

BaseTimedElement::BaseTimedElement()
{ 
  setWaitTimeOnce(0);
}

void BaseTimedElement::setWaitTimeOnce(int ms)
{
  _ms = ms;
  _every = false;
  _passed = false;
  _endMillis = millis() + ms;
}

void BaseTimedElement::setWaitTimeEvery(int ms)
{
  setWaitTimeOnce(ms);
  _every = true;
}

bool BaseTimedElement::waitTimePassed()
{
  if (_ms <= 0 || _passed || millis() < _endMillis || millis() > _endMillis + 10000)
    return false;
    
  if (_every)
    _endMillis += _ms;
  else
    _passed = true;
  
  return true;
}

void BaseTimedElement::waitTimeStop()
{
  _ms = 0;
}