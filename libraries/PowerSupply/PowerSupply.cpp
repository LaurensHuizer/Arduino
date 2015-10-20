/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling a power supply from a pc.
  You'll need to connect the green wire to a output bus and any of the red wires to an input bus on 
  the Arduino.
  This class can coop with simple on/off scenarios and has overload protection build in.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Create an instance of this class and provide the pins on which the green and red wires are connected.
  You can either set autorecovery or act on overload with custom code.

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 3rd, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/blog/arduino/power-source-library


  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

#define RestoreFailureDetected 0
#define RestorePoweringDown 1
#define RestoringPower 2

#include "Arduino.h"
#include "PowerSupply.h"
#include "BaseTimedElement.h"

PowerSupply::PowerSupply(int pinPowerSupply, int pinPhaseCheck)
 : BaseTimedElement()
{
  _pinPowerSupply = pinPowerSupply;
  _pinPhaseCheck = pinPhaseCheck;
  pinMode(_pinPowerSupply, OUTPUT);
  pinMode(_pinPhaseCheck, INPUT);
  turnOff();
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

PowerSupply *PowerSupply::subscribeOverloadProtection(void (*method)())
{
  _overloadProtection = method;
  return this;
}

PowerSupply *PowerSupply::setAutoRecovery(bool autoRecovery)
{
  _autoRecovery = autoRecovery;
  return this;
}

PowerSupply *PowerSupply::turnOn()
{
  digitalWrite(_pinPowerSupply, LOW);
  _power = true;
  return this;
}

PowerSupply *PowerSupply::turnOff()
{
  digitalWrite(_pinPowerSupply, HIGH);
  _power = false;
  return this;
}

bool PowerSupply::isOn()
{
  return digitalRead(_pinPhaseCheck) == HIGH;
}

void PowerSupply::update()
{
  if (!_power || isOn())
  {
    _resetStep = RestoreFailureDetected;
    return;
  }

  switch (_resetStep)
  {
    case RestoreFailureDetected:
      setWaitTimeOnce(750);
      _resetStep = RestorePoweringDown;
      break;
    case RestorePoweringDown:
      if (_overloadProtection)
        _overloadProtection();
      
      if (waitTimePassed())
      {
        digitalWrite(_pinPowerSupply, HIGH);
        setWaitTimeOnce(1500);
        _resetStep = RestoringPower;
      }
      break;
    case RestoringPower:
      if (waitTimePassed())
      {
        digitalWrite(_pinPowerSupply, LOW);
        _resetStep = RestoreFailureDetected;
      }
      break;
  }
}