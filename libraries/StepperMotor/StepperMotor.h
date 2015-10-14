/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling stepper motors that are controlled by a 4 pin controller board.
  It is tested and developed using the 28BYJ-48 stepper motor and the ULN2003 driver board.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  The 28BYJ-48 motor has 512 full engine rotations to rotate the drive shaft once.
  In half-step mode these are 8 x 512 = 4096 steps for a full rotation, and in full-step mode these are
  4 x 512 = 2048 steps for a full rotation.
  See Example.ino how to use this class with the use of the movementCompletionHandler.

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

#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"
#include "BaseTimedElement.h"

class StepperMotor : public BaseTimedElement
{
  public:
    StepperMotor(int pinA, int pinB, int pinC, int pinD);
    StepperMotor* setStepMode(int stepMode);
    StepperMotor* setStepDelay(int ms);
    StepperMotor* addMovementCompletionHandler(void (*movementCompleted)());
    void rotateClockwise();
    void rotateClockwise(int steps);
    void rotateCounterClockwise();
    void rotateCounterClockwise(int steps);
    void update();
    void stop();
    
    static const short halfStep = 1;
    static const short fullStepSinglePhase = 2;
    static const short fullStepDualPhase = 3;
  private:
    void setRotationDirection(int direction, int steps);
    void applyEngineStep();

    //constructor variables
    int _pinA;
    int _pinB;
    int _pinC;
    int _pinD;
    
    //other variables
    void (*_movementCompleted)();
    int _mode = 0;
    int _steps = -1;
    int _delayMs = 1;
    int _engineStep = 0;
    int _currentStep = 0;
    int _rotationDirection = 0;
};

#endif