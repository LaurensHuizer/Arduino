/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for the execution of event methods based upon specified integer values.
  You can specify checks for the value to be equal to, higher than, lower than, between or not between
  specific values.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  You can create a EventList per variable you want to check. New events can be added by calling any of
  the add methods:
  - addEqualTo(int value, void (*callMethod)());
  - addGreaterThan(int value, void (*callMethod)());
  - addSmallerThen(int value, void (*callMethod)());
  - addBetween(int lowerValue, int upperValue, void (*callMethod)());
  - addNotBetween(int lowerValue, int upperValue, void (*callMethod)());
  
  To check all the events from the EventList, call the checkEvents method and provide the value.
  
  The handler method will only be called once when the value matches the requirements.
  When the value doens't match anymore the class will reset the validation to work again.
  
  For example; when you set the checkvalue to 'smaller than 5' and the value drops to 4, the handler
  method will be called. When the value drops to 3, the class will not call the method again. When the
  value gets to 6, the validation will be reset, so when the value drops to 4 again, the handler will
  call the method once again.

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, December 12th, 2015.
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
#include "EventList.h"

#define isEqualTo 0
#define isGreaterThan 1
#define isSmallerThan 2
#define isBetween 3
#define isNotBetween 4


/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

EventList* EventList::addEqualTo(int value, void (*callMethod)())
{
  addEvent(isEqualTo, value, 0, callMethod);
  return this;
}

EventList* EventList::addGreaterThan(int value, void (*callMethod)())
{
  addEvent(isGreaterThan, value, 0, callMethod);
  return this;
}

EventList* EventList::addSmallerThen(int value, void (*callMethod)())
{
  addEvent(isSmallerThan, value, 0, callMethod);
  return this;
}

EventList* EventList::addBetween(int lowerValue, int upperValue, void (*callMethod)())
{
  addEvent(isBetween, lowerValue, upperValue, callMethod);
  return this;
}

EventList* EventList::addNotBetween(int lowerValue, int upperValue, void (*callMethod)())
{
  addEvent(isNotBetween, lowerValue, upperValue, callMethod);
  return this;
}

void EventList::checkEvents(int value)
{
  if (!_events)
    return;
  
  checkEvent(*_events, value);
}

/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

void EventList::addEvent(short equalityCheck, int lowerValue, int upperValue, void (*callMethod)())
{
  if ((equalityCheck == isBetween || equalityCheck == isNotBetween) && upperValue < lowerValue)
  {
    int tempUpper = upperValue;
    upperValue = lowerValue;
    lowerValue = tempUpper;
  }
  
  if (_events)
  {
    EventList::addEvent(*_events, equalityCheck, lowerValue, upperValue, callMethod);
  }
  else
  {
    _events = new CheckEvent(equalityCheck, lowerValue, upperValue, callMethod);
  }
}

void EventList::addEvent(CheckEvent &checkEvent, short equalityCheck, int lowerValue, int upperValue, void (*callMethod)())
{
  if (checkEvent.nextEvent)
  {
    EventList::addEvent(*checkEvent.nextEvent, equalityCheck, lowerValue, upperValue, callMethod);
  }
  else
  {
    checkEvent.nextEvent = new CheckEvent(equalityCheck, lowerValue, upperValue, callMethod);
  }
}

void EventList::checkEvent(CheckEvent &checkEvent, int value)
{
  if (checkEvent.isInvoked)
    checkInvokedEvent(checkEvent, value);
  else
    checkNotInvokedEvent(checkEvent, value);
  
  if (checkEvent.nextEvent)
    EventList::checkEvent(*checkEvent.nextEvent, (int)value);
}

void EventList::checkInvokedEvent(CheckEvent &checkEvent, int value)
{
  switch (checkEvent.equalityCheck)
  {
    case isEqualTo:
      if (value != checkEvent.lowerValue)
        checkEvent.isInvoked = false;
      break;
    case isGreaterThan:
      if (value < checkEvent.lowerValue)
        checkEvent.isInvoked = false;
      break;
    case isSmallerThan:
      if (value > checkEvent.lowerValue)
        checkEvent.isInvoked = false;
      break;
    case isBetween:
      if (value < checkEvent.lowerValue || value > checkEvent.upperValue)
        checkEvent.isInvoked = false;
      break;
    case isNotBetween:
      if (value >= checkEvent.lowerValue && value <= checkEvent.upperValue)
        checkEvent.isInvoked = false;
      break;
  }
  if (checkEvent.nextEvent)
    EventList::checkEvent(*checkEvent.nextEvent, value);
}

void EventList::checkNotInvokedEvent(CheckEvent &checkEvent, int value)
{
  switch (checkEvent.equalityCheck)
  {
    case isEqualTo:
      if (value == checkEvent.lowerValue)
      {
        checkEvent.isInvoked = true;
        checkEvent.callMethod();
      }
      break;
    case isGreaterThan:
      if (value > checkEvent.lowerValue)
      {
        checkEvent.isInvoked = true;
        checkEvent.callMethod();
      }
      break;
    case isSmallerThan:
      if (value < checkEvent.lowerValue)
      {
        checkEvent.isInvoked = true;
        checkEvent.callMethod();
      }
      break;
    case isBetween:
      if (value >= checkEvent.lowerValue && value <= checkEvent.upperValue)
      {
        checkEvent.isInvoked = true;
        checkEvent.callMethod();
      }
      break;
    case isNotBetween:
      if (value < checkEvent.lowerValue || value > checkEvent.upperValue)
      {
        checkEvent.isInvoked = true;
        checkEvent.callMethod();
      }
      break;
  }
  if (checkEvent.nextEvent)
    EventList::checkEvent(*checkEvent.nextEvent, value);
}