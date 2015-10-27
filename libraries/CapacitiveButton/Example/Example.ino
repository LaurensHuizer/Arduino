/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class makes life a lot simpler when you use capacitive buttons. The class detects clicks,
  double clicks, holds and releases of the button and calls methods based upon that.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  You can subscribe to 4 events with a void() method as parameter that is called when the event occurs.
  Use these methods to subscribe:
  
  - subscribeClick
  - subscribeDoubleClick
  - subscribeHold
  - subscribeHoldRelease

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

// Both the BaseTimedElement class and the CapacitiveButton class must be referenced
#include <CapacitiveButton.h>
#include <BaseTimedElement.h>

// Change the pin-number to match the connected pin of the capacitive button on your Arduino
CapacitiveButton button(A0);

// This demo method is called when you tap the button once
void click()
{
  Serial.println("click");
}

// This demo method is called when you double tap the button
void doubleClick()
{
  Serial.println("double click");
}

// This demo method is called when you hold the button
void hold()
{
  Serial.println("hold");
}

// This demo method is called when you release the button after holding it
void release()
{
  Serial.println("release");
}

void setup()
{
  // We are going to print events to serial. To see them open the Serial monitor
  Serial.begin(9600);
  // Connect our demo methods to the events
  button.subscribeClick(&click)
        -> subscribeDoubleClick(&doubleClick)
        -> subscribeHold(&hold)
        -> subscribeHoldRelease(&release);
}

void loop()
{
  // This function is required to be called in the loop in order for the button to work!
  button.update();
}