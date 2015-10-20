/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling a power supply from a pc.
  You'll need to connect the green wire to a output bus and any of the red wires to an input bus on 
  the Arduino.
  This class can coop with simple on/off scenarios and has overload protection build in.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  Provides a simple, stable way or supplying power to your setup using a power supply from a pc.
  Keep in mind that on overload the power will go down for some time! If this effects your process
  you should subscribe to the overloadProtection event and wait until the power is back on.
  
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

// Both the BaseTimedElement class and the PowerSupply class must be referenced
#include <BaseTimedElement.h>
#include <PowerSupply.h>

// Change the pin-numbers to match the connected pin on your Arduino board to the green
// and the red wire. The red wire can also be connected to a digital input.
PowerSupply powerSupply(13, A1);

void onOverload()
{
  // Do something with the overload; 
  // For example: you could set a boolean to check wait for the power to be back up.
  // In the loop() method you can check if the power supply using the IsOn() method 
}

void setup()
{
  powerSupply.setAutoRecovery(true) //set auto recovery to true
             -> subscribeOverloadProtection(&onOverload)
             -> turnOn();
}

void loop()
{
  // This function is required to be called in the loop in order for the buttons to work!
  powerSupply.update();
}