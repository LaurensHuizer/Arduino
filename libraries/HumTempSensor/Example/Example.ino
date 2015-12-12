/* _______________________
  /   SHORT DESCRIPTION   \____________________________________________________________________________
  This example shows how to control the DHT11 Digital Temperature Humidity Sensor Module using the 
  HumTempSensor class.

   _______________________
  /    BACKGROUND INFO    \____________________________________________________________________________
  You have to keep in mind that the reading of the Temperature Humidity Sensor Module is not very fast.
  Normal operation time will be somewhere between 1682µs and 3320µs, and the maximum theoritical 
  operation time is 8158µs.
  
  During this 1ms - 3 ms your Arduino will be exclusively busy reading the sensor, thus not responsing
  to any other logic flows except interrupt flows.

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

// The HumTempSensor class uses both the BaseTimedElement class and the EventList class.
#include <BaseTimedElement.h>
#include <HumTempSensor.h>
#include <EventList.h>

// Change the pin-numbers to match the connected pin from your Arduino board to the shield
// This has to be an analogue pin!
HumTempSensor humTempSensor(A0);

// This demo method prints the temperature and humidity to the serial port
int lastHumidity = 0;
int lastTemperature = 0;
void printTemperatureIfChanged()
{
  if (lastHumidity != humTempSensor.humidity || lastTemperature != humTempSensor.temperature)
  {
    lastHumidity = humTempSensor.humidity;
    lastTemperature = humTempSensor.temperature;
    Serial.print("Current humidity: ");
    Serial.print(humTempSensor.humidity);
    Serial.print("  temperature: ");
    Serial.print(humTempSensor.temperature);
    Serial.println("^C");
  }
}

// These test methods will be called based upon check values.
// See the setup() method for this
void veryHumid()
{
  Serial.println("It is getting rather moist over here!");
}

void normalHumidity()
{
  Serial.println("I'm starting to like the humidity");
}

void niceTemperature()
{
  Serial.println("I'm starting to feel warm and cozy");
}

void temperatureOk()
{
  Serial.println("I'm liking the current temperature");
}

void temperatureChange()
{
  Serial.println("Please change the temperature");
}

void quiteCold()
{
  Serial.println("Brrr... starting to get cold");
}

void setup()
{
  //To quickly test the humidity and temperature you can breathe hot air into your sensor.
  humTempSensor.humidityEvents
               .addGreaterThan(60, &veryHumid)
              ->addSmallerThen(40, &normalHumidity);

  //Change these values to match your surroundings
  humTempSensor.temperatureEvents
               .addGreaterThan(27, &niceTemperature)
              ->addBetween(23, 27, &temperatureOk)
              ->addNotBetween(23, 30, &temperatureChange)
              ->addSmallerThen(23, &quiteCold);

  //You can also change to Fahrenheit with the .inFahrenheit() method
  Serial.begin(9600);
  Serial.println("BEGIN");
}

void loop()
{
  humTempSensor.update();
  if (humTempSensor.initialized)
    printTemperatureIfChanged();
}