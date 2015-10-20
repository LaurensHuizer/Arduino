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

#ifndef PowerSupply_h
#define PowerSupply_h

#include "Arduino.h"
#include "BaseTimedElement.h"

class PowerSupply : public BaseTimedElement
{
  public:
    PowerSupply(int pinPowerSupply, int pinPhaseCheck);
    PowerSupply *subscribeOverloadProtection(void (*method)());
    PowerSupply *setAutoRecovery(bool autoRecovery);
    PowerSupply *turnOn();
    PowerSupply *turnOff();
    bool isOn();
    void update();
  private:
    //constructor variables
    int _pinPowerSupply;
    int _pinPhaseCheck;
    
    //other variables
    bool _autoRecovery = false;
    void (*_overloadProtection)();
    bool _power = false;
    short _resetStep = 0;
};

#endif