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

#include "Arduino.h"
#include "StepperMotor.h"
#include "BaseTimedElement.h"

#define stopped 0
#define clockwise 1
#define counterClockwise 2

StepperMotor::StepperMotor(int pinA, int pinB, int pinC, int pinD)
 : BaseTimedElement()
{
  _pinA = pinA;
  _pinB = pinB;
  _pinC = pinC;
  _pinD = pinD;
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  setWaitTimeEvery(_delayMs);
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

StepperMotor* StepperMotor::setStepMode(int stepMode)
{
  _mode = stepMode;
  return this;
}

StepperMotor* StepperMotor::setStepDelay(int ms)
{
  _delayMs = ms > 1 ? ms : 1;
  setWaitTimeEvery(_delayMs);
  return this;
}

StepperMotor* StepperMotor::addMovementCompletionHandler(void (*movementCompleted)())
{
  _movementCompleted = movementCompleted;
  return this;
}

void StepperMotor::rotateClockwise()
{
  setRotationDirection(clockwise, -1);
}

void StepperMotor::rotateClockwise(int steps)
{
  setRotationDirection(clockwise, steps);
}

void StepperMotor::rotateCounterClockwise()
{
  setRotationDirection(counterClockwise, -1);
}

void StepperMotor::rotateCounterClockwise(int steps)
{
  setRotationDirection(counterClockwise, steps);
}

void StepperMotor::update()
{
  if (!waitTimePassed() || _rotationDirection == stopped)
    return;

  if (_rotationDirection == clockwise)
    _engineStep = _engineStep - 1 < 1 ? 8 : _engineStep - 1;
  else
    _engineStep = _engineStep + 1 > 8 ? 1 : _engineStep + 1;
  
  applyEngineStep();
  
  if (_steps > 0)
  {
    _currentStep++;
    if (_currentStep >= _steps)
    {
      waitTimeStop();
      _rotationDirection = stopped;
      if (_movementCompleted);
        _movementCompleted();
    }
  }
}

void StepperMotor::stop()
{
  waitTimeStop();
  _rotationDirection = stopped;
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
}


/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

void StepperMotor::setRotationDirection(int direction, int steps)
{
  _rotationDirection = direction;
  _steps = steps;
  _currentStep = 0;
  setWaitTimeEvery(_delayMs);
}

void StepperMotor::applyEngineStep()
{
  if (_mode == halfStep)
  {
    digitalWrite(_pinA, _engineStep == 8 || _engineStep == 1 || _engineStep == 2 ? HIGH : LOW);
    digitalWrite(_pinB, _engineStep == 2 || _engineStep == 3 || _engineStep == 4 ? HIGH : LOW);
    digitalWrite(_pinC, _engineStep == 4 || _engineStep == 5 || _engineStep == 6 ? HIGH : LOW);
    digitalWrite(_pinD, _engineStep == 6 || _engineStep == 7 || _engineStep == 8 ? HIGH : LOW);
  }
  else if (_mode == fullStepSinglePhase)
  {
    digitalWrite(_pinA, _engineStep == 1 || _engineStep == 5 ? HIGH : LOW);
    digitalWrite(_pinB, _engineStep == 2 || _engineStep == 6 ? HIGH : LOW);
    digitalWrite(_pinC, _engineStep == 3 || _engineStep == 7 ? HIGH : LOW);
    digitalWrite(_pinD, _engineStep == 4 || _engineStep == 8 ? HIGH : LOW);
  }
  else if (_mode == fullStepDualPhase)
  {
    digitalWrite(_pinA, _engineStep == 1 || _engineStep == 4 || _engineStep == 5 || _engineStep == 8 ? HIGH : LOW);
    digitalWrite(_pinB, _engineStep == 1 || _engineStep == 2 || _engineStep == 5 || _engineStep == 6 ? HIGH : LOW);
    digitalWrite(_pinC, _engineStep == 2 || _engineStep == 3 || _engineStep == 6 || _engineStep == 7 ? HIGH : LOW);
    digitalWrite(_pinD, _engineStep == 3 || _engineStep == 4 || _engineStep == 7 || _engineStep == 8 ? HIGH : LOW);
    
  }
}