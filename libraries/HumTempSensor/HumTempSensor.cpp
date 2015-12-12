/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This class is for controlling the DHT11 Digital Temperature Humidity Sensor Module. By default this
  class uses degrees celcius, but you can also switch this to degrees Fahrenheit by calling the 
  inFahrenheit method.
  You can subscribe event methods based upon specific values for the temperature and for specific
  values for the humidity. See the Example.ino for more details about that.

   _______________________
  /  USAGE OF THIS CLASS  \____________________________________________________________________________
  Create an instance of this class. By default the sensor is read every 2 seconds, you can specify
  another read interval in seconds calling the setReadInterval method. You can simply read the
  temperature and humidity values, or add events based upon the values of them.

   _______________________
  / AUTHOR & TERMS OF USE \____________________________________________________________________________
  Created by Laurens Huizer, December 12th, 2015.
   _                                _           _                    _ 
  | | __ _ _   _ _ __ ___ _ __  ___| |__  _   _(_)_______ _ __ _ __ | |
  | |/ _` | | | | '__/ _ \ '_ \/ __| '_ \| | | | |_  / _ \ '__| '_ \| |
  | | (_| | |_| | | |  __/ | | \__ \ | | | |_| | |/ /  __/ |_ | | | | |
  |_|\__,_|\__,_|_|  \___|_| |_|___/_| |_|\__,_|_/___\___|_(_)|_| |_|_|
  http://www.laurenshuizer.nl/blog/arduino/humidity-temperature-sensor-library
  

  This is free software. 
  You can redistribute it and/or modify it under the terms of GNU General Public License 3.0. 
  To view a copy of this license, visit http://www.gnu.org/licenses/gpl-3.0.txt

   _______________________
  /    CHANGE HISTORY     \____________________________________________________________________________
  
  CHANGED BY               | DATE       | DESCRIPTION
  -------------------------+------------+--------------------------------------------------------------
  <name>                   | yyyy-mm-dd | <description>
*/

#define SensorInit 1
#define SensorReadValues 2

#include "Arduino.h"
#include "HumTempSensor.h"
#include "EventList.h"
#include "BaseTimedElement.h"

HumTempSensor::HumTempSensor(int pinSensor)
 : BaseTimedElement()
{
  _pinSensor = pinSensor;
  pinMode(pinSensor, INPUT);
  setWaitTimeEvery(100);
}

/*****************************\
| P U B L I C   M E T H O D S |
\*****************************/

HumTempSensor* HumTempSensor::setReadInterval(short interval)
{
  _interval = interval > 1 ? interval : 1;
  return this;
}

HumTempSensor* HumTempSensor::inFahrenheit()
{
  _fahrenheit = true;
  return this;
}

void HumTempSensor::update()
{
  if (waitTimePassed())
  {
    switch (_sensorState)
    {
      case SensorInit:
        pinMode(_pinSensor, OUTPUT);
        digitalWrite(_pinSensor, LOW);
        setWaitTimeOnce(20);
        break;
      case SensorReadValues:
        digitalWrite(_pinSensor, HIGH);
        delayMicroseconds(40);
        sensorRead();
        if (initialized)
        {
          humidityEvents.checkEvents(humidity);
          temperatureEvents.checkEvents(temperature);
        }
        if (!initialized && temperature > 0 || humidity > 0)
        {
          _initializeCycle--;
          if (_initializeCycle == 0)
            initialized = true;
        }
        setWaitTimeOnce(_interval * 1000);
        break;
    }
    _sensorState++;
    if (_sensorState > SensorReadValues)
      _sensorState = SensorInit;
  }
}

/*******************************\
| P R I V A T E   M E T H O D S |
\*******************************/

void HumTempSensor::sensorRead()
{
	pinMode(_pinSensor, INPUT);

  if (!sensorLostState(LOW))
    return;

  if (!sensorLostState(HIGH))
    return;

  uint8_t hum = getByte();
  uint8_t check1 = getByte();
  uint8_t temp = getByte();
  uint8_t check2 = getByte();
  uint8_t checksum = getByte();
  
  if (check1 + check2 == 0 && check1 + check2 != checksum)
  {
    humidity = hum;
    temperature = _fahrenheit
                  ? temp*9/5+32
                  : temp;
  }
}

uint8_t HumTempSensor::getByte()
{
  uint8_t value = 0;
  
	// read the 8 bits
	for (uint8_t bit = 7; bit < 8; bit--)
	{
    if (!sensorLostState(LOW))
      return 255;

    unsigned long startMicros = micros();

    if (!sensorLostState(HIGH))
      return 255;

    if (micros() - startMicros > 40)
      value |= (1 << bit);
  }
  return value;
}

bool HumTempSensor::sensorLostState(int state)
{
  unsigned long startMicros = micros();
	while(digitalRead(_pinSensor) == state)
  {
		if (micros() - startMicros > 100)
      return false;
  }
  return true;
}