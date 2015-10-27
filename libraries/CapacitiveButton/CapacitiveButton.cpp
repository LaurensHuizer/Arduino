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

#define Released 0
#define VerifyRelease 1
#define Pressed 2
#define VerifyPress 3
#define DoublePressed 4
#define VerifyDoublePress 5
#define VerifyDoublePressRelease 6
#define HeldDown 7
#define VerifyHeldDownRelease 8

#include "Arduino.h"
#include "CapacitiveButton.h"
#include "BaseTimedElement.h"

CapacitiveButton::CapacitiveButton(int pinButton)
 : BaseTimedElement()
{
  _pinButton = pinButton;
  pinMode(pinButton, INPUT_PULLUP);
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

CapacitiveButton *CapacitiveButton::subscribeClick(void (*method)())
{
  _click = method;
  return this;
}

CapacitiveButton *CapacitiveButton::subscribeDoubleClick(void (*method)())
{
  _doubleClick = method;
  return this;
}

CapacitiveButton *CapacitiveButton::subscribeHold(void (*method)())
{
  _hold = method;
  return this;
}

CapacitiveButton *CapacitiveButton::subscribeHoldRelease(void (*method)())
{
  _release = method;
  return this;
}

void CapacitiveButton::update()
{
  bool pressed = digitalRead(_pinButton) == HIGH;
  bool timePassed = waitTimePassed();
  
  switch (_state)
  {
    case VerifyRelease:
      setTimeoutAndStateAndCall(pressed, 25, VerifyDoublePress, NULL);
      stopTimeoutAndSetStateAndCall(!pressed && timePassed, Released, _click);
      break;
    case Released:
      setTimeoutAndStateAndCall(pressed, 25, VerifyPress, NULL);
      break;
    case VerifyPress:
      stopTimeoutAndSetStateAndCall(!pressed, Released, NULL);
      setTimeoutAndStateAndCall(pressed && timePassed, 350, Pressed, NULL);
      break;
    case Pressed:
      setTimeoutAndStateAndCall(!pressed, 200, VerifyRelease, NULL);
      stopTimeoutAndSetStateAndCall(pressed && timePassed, HeldDown, _hold);
      break;
    case VerifyDoublePress:
      setTimeoutAndStateAndCall(!pressed, 200, VerifyRelease, NULL);
      setTimeoutAndStateAndCall(pressed && timePassed, 350, DoublePressed, NULL);
      break;
    case DoublePressed:
      setTimeoutAndStateAndCall(!pressed, 25, VerifyDoublePressRelease, NULL);
      stopTimeoutAndSetStateAndCall(pressed && timePassed, HeldDown, _hold);
      break;
    case VerifyDoublePressRelease:
      setTimeoutAndStateAndCall(pressed, 1000, DoublePressed, NULL);
      stopTimeoutAndSetStateAndCall(!pressed && timePassed, Released, _doubleClick);
      break;
    case HeldDown:
      setTimeoutAndStateAndCall(!pressed, 25, VerifyHeldDownRelease, NULL);
      break;
    case VerifyHeldDownRelease:
      stopTimeoutAndSetStateAndCall(pressed, HeldDown, NULL);
      stopTimeoutAndSetStateAndCall(!pressed && timePassed, Released, _release);
      break;
  }
}


/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

void CapacitiveButton::setTimeoutAndStateAndCall(bool performActions, int timeout, short state, void (*method)())
{
  if (performActions)
  {
    setWaitTimeOnce(timeout);
    _state = state;
    if (method)
      method();
  }
}

void CapacitiveButton::stopTimeoutAndSetStateAndCall(bool performActions, short state, void (*method)())
{
  if (performActions)
  {
    waitTimeStop();
    _state = state;
    if (method)
      method();
  }
}