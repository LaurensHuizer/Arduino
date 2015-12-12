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

#ifndef EventList_h
#define EventList_h

#include "Arduino.h"

struct CheckEvent
{
  CheckEvent(short cEqualityCheck, int cLowerValue, int cUpperValue, void (*cCallMethod)()) 
     : equalityCheck(cEqualityCheck), lowerValue(cLowerValue), upperValue(cUpperValue), callMethod(cCallMethod) {}
  short equalityCheck;
  int lowerValue;
  int upperValue;
  void (*callMethod)();
  bool isInvoked = false;
  CheckEvent *nextEvent = NULL;
};

class EventList
{
  public:
    EventList* addEqualTo(int value, void (*callMethod)());
    EventList* addGreaterThan(int value, void (*callMethod)());
    EventList* addSmallerThen(int value, void (*callMethod)());
    EventList* addBetween(int lowerValue, int upperValue, void (*callMethod)());
    EventList* addNotBetween(int lowerValue, int upperValue, void (*callMethod)());
    void checkEvents(int value);
    
  private:
    void addEvent(short equalityCheck, int lowerValue, int upperValue, void (*callMethod)());
    static void addEvent(CheckEvent &checkEvent, short equalityCheck, int lowerValue, int upperValue, void (*callMethod)());
    static void checkEvent(CheckEvent &checkEvent, int value);
    static void checkInvokedEvent(CheckEvent &checkEvent, int value);
    static void checkNotInvokedEvent(CheckEvent &checkEvent, int value);
    
    CheckEvent* _events = NULL;
};

#endif