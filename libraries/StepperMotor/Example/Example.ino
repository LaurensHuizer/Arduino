/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling stepper motors that are controlled by a 4 pin controller board.
  It is tested and developed using the 28BYJ-48 stepper motor and the ULN2003 driver board.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  The 28BYJ-48 motor has 512 full engine rotations to rotate the drive shaft once.
  In half-step mode these are 8 x 512 = 4096 steps for a full rotation, and in full-step mode these are
  4 x 512 = 2048 steps for a full rotation.
  
  This example code is to turn the motor clockwise and counterclockwise in full-step mode and half-step
  mode for a specific number of steps. You could also set the motor to turn eternally in one direction
  by calling RotateClockwise() or RotateCounterClockwise() without any parameters.

  Note: full rotation with 1ms rotation delay will probably only work when your driver board is powered 
  by an external power supply!

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, October 2nd, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/blog/arduino/stepper-motor-library 


  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

// Both the BaseTimedElement class and the StepperMotor class must be referenced
#include <BaseTimedElement.h>
#include <StepperMotor.h> 

// Change the pin-numbers to match the connected pins from your Arduino board to the driverboard
StepperMotor motor(8, 9, 10, 11);
bool clockwise = true; // Demo variable, to move the motor clockwise and counterclockwise

// This method is being called when the motor has completed the amount of steps
// You are allowed to change the MovementCompletionHandler in this method,
// but for this example we've simply used a boolean to switch between clockwise and counterclockwise.
void movementCompleted()
{
  clockwise = !clockwise; // For this demo invert clockwise, to move back and forth
  if (clockwise)
  {
    motor.setStepMode(StepperMotor::fullStepDualPhase) // Set motor to perform full steps (2048 = 360 degrees, based on 28BYJ-48)
         -> setStepDelay(4)        // Set a delay between each step of 4 ms
         -> rotateClockwise(1024); // Perform 1024 steps (rotate the shaft 180 degrees, based on 28BYJ-48)
  }
  else
  {
    motor.setStepMode(StepperMotor::halfStep) // Set motor to perform half steps (4096 = 360 degrees, based on 28BYJ-48)
         -> setStepDelay(1)                   // Set a delay between each step of 1 ms
         -> rotateCounterClockwise(4096);     // Perform 4096 steps (rotate the shaft 360 degrees, based on 28BYJ-48)
  }
}

void setup() 
{
  //setup of the motor, all these methods 
  motor.setStepMode(StepperMotor::fullStepSinglePhase) // Set motor to perform full steps (2048 = 360 degrees, based on 28BYJ-48)
       -> addMovementCompletionHandler(&movementCompleted) // Add a method that is called when the motor has performed the amount of steps
       -> setStepDelay(4)              // Set a delay between each step of 4 ms
       -> rotateClockwise(1024);       // Perform 2048 steps (rotate the shaft 180 degrees, based on 28BYJ-48)
}

void loop() 
{
  // This function is required to be called in the loop in order for the motor to work!
  motor.update();
}