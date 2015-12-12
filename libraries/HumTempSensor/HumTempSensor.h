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

#ifndef HumTempSensor_h
#define HumTempSensor_h

#include "Arduino.h"
#include "EventList.h"
#include "BaseTimedElement.h"

class HumTempSensor : public BaseTimedElement
{
  public:
    HumTempSensor(int pinSensor);
    HumTempSensor* setReadInterval(short interval);
    HumTempSensor* inFahrenheit();
    void update();

    int humidity = 0;
    int temperature = 0;
    bool initialized = false;
    EventList humidityEvents;
    EventList temperatureEvents;
    
  private:
    void sensorRead();
    uint8_t getByte();
    bool sensorLostState(int state);
  
    //constructor variables
    int _pinSensor;
    int _sensorState = 0;
    
    //other variables
    short _interval = 2;
    short _initializeCycle = 3;
    bool _fahrenheit = false;
};

#endif