/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class makes life a lot simpler when you use capacitive buttons. The class detects clicks,
  double clicks, holds and releases of the button and calls methods based upon that.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Create an instance of this class and subscribe to the desired events.

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 27th, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/arduino/capacitive-button-library
  

  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

#ifndef CapacitiveButton_h
#define CapacitiveButton_h

#include "Arduino.h"
#include "BaseTimedElement.h"

class CapacitiveButton : public BaseTimedElement
{
  public:
    CapacitiveButton(int pinButton);
    CapacitiveButton *subscribeClick(void (*method)());
    CapacitiveButton *subscribeDoubleClick(void (*method)());
    CapacitiveButton *subscribeHold(void (*method)());
    CapacitiveButton *subscribeHoldRelease(void (*method)());
    void update();
  private:
    void setTimeoutAndStateAndCall(bool performActions, int timeout, short state, void (*method)());
    void stopTimeoutAndSetStateAndCall(bool performActions, short state, void (*method)());

    //constructor variables
    int _pinButton;

    //other variables
    short _state;
    short _pressState;
    void (*_click)();
    void (*_doubleClick)();
    void (*_hold)();
    void (*_release)();
};

#endif