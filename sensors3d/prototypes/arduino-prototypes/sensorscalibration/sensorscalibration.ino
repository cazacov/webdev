#include <Wire.h>

#include "sensors.h"

Sensors sensors; 


void setup(void) 
{
  Serial.begin(115200);
  sensors.init();
}


void loop(void) 
{
  Serial.println("Calibrating magnetometer...");
  Serial.println("Please rotate the sensor in all possible directions for 60 seconds");  
  
  int maxX = -30000;
  int minX = +30000;  
  int maxY = -30000;
  int minY = +30000;  
  int maxZ = -30000;
  int minZ = +30000;  
  
  for (int j = 60; j >= 0; j--)
  {
    Serial.println(j);
    long stopTime = millis() + 1000L;
  
    while (millis() < stopTime) 
    {  
      int  imx;
      int  imy;    
      int  imz;
      sensors.readMagnetometer(imx, imy, imz);    
      
      if (imx > maxX) maxX = imx;
      if (imy > maxY) maxY = imy;
      if (imz > maxZ) maxZ = imz;    
      if (imx < minX) minX = imx;
      if (imy < minY) minY = imy;
      if (imz < minZ) minZ = imz;    
      
      delay(10);
    }
  }
  
  char buf[80];
  
  int cX = ((long)maxX + minX) / 2;
  int cY = ((long)maxY + minY) / 2;
  int cZ = ((long)maxZ + minZ) / 2;  
    
  sprintf(buf, "%d,%d,%d", cX, cY, cZ);
  Serial.println(buf);
}
