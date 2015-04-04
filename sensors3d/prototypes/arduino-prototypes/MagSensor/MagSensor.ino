/***************************************************************************
  This is a library example for the HMC5883 magnentometer/compass

  Designed specifically to work with the Adafruit HMC5883 Breakout
  http://www.adafruit.com/products/1746
 
  *** You will also need to install the Adafruit_Sensor library! ***

  These displays use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries with some heading example from
  Love Electronics (loveelectronics.co.uk)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop(void) 
{
  double minX = 1000;
  double maxX = -1000;  
  double minY = 1000;
  double maxY = -1000;  
  double minZ = 1000;
  double maxZ = -1000;  
  
  Serial.println("Calibrating...");
  long stopTime = millis() + 60000;
  
  while (millis() < stopTime)
  {
    sensors_event_t event; 
    mag.getEvent(&event);
    if (event.magnetic.x < minX)
    {
      minX = event.magnetic.x;
    }
    if (event.magnetic.y < minY)
    {
      minY = event.magnetic.y;
    }
    if (event.magnetic.z < minZ)
    {
      minZ = event.magnetic.z;
    }
    if (event.magnetic.x > maxX)
    {
      maxX = event.magnetic.x;
    }
    if (event.magnetic.y > maxY)
    {
      maxY = event.magnetic.y;
    }
    if (event.magnetic.z > maxZ)
    {
      maxZ = event.magnetic.z;
    }
    delay(10);
  }

  Serial.print("MinX: "); Serial.print(minX); Serial.print("  ");
  Serial.print("MinY: "); Serial.print(minY); Serial.print("  ");
  Serial.print("MinZ: "); Serial.print(minZ); Serial.print("  ");Serial.println("");      
  Serial.print("MaxX: "); Serial.print(maxX); Serial.print("  ");
  Serial.print("MaxY: "); Serial.print(maxY); Serial.print("  ");
  Serial.print("MaxZ: "); Serial.print(maxZ); Serial.print("  ");Serial.println("");      
    
  double cX = (maxX + minX) / 2;
  double cY = (maxY + minY) / 2;  
  double cZ = (maxZ + minZ) / 2;    
  
  Serial.print("CX: "); Serial.print(cX); Serial.print("  ");
  Serial.print("CY: "); Serial.print(cY); Serial.print("  ");
  Serial.print("CZ: "); Serial.print(cZ); Serial.print("  ");Serial.println("");      

  
  while (1) 
  {  
    /* Get a new sensor event */ 
    sensors_event_t event; 
    mag.getEvent(&event);

     /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
    Serial.print("X: "); Serial.print(event.magnetic.x - cX); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.magnetic.y - cY); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.magnetic.z - cZ); Serial.print("  ");Serial.println("uT");
    delay(100);
  }
}
