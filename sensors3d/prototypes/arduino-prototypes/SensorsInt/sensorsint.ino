#include <Wire.h>

#include "sensors.h"
Sensors sensors; 

#include "filter.h"
Filter fax;
Filter fay;
Filter faz;
Filter fmx;
Filter fmy;
Filter fmz;

void setup(void) 
{
  Serial.begin(115200);
  sensors.init();
}


void loop(void) 
{
  int ax,ay,az, mx,my,mz;
  
  sensors.readAccelerometer(ax, ay, az);
  sensors.readMagnetometer(mx, my, mz);  
  
  ax = fax.filter(ax);
  ay = fay.filter(ay);  
  az = faz.filter(az);    
  mx = fax.filter(mx);
  my = fay.filter(my);  
  mz = faz.filter(mz);    
  
  char buf[80];
  sprintf(buf, "A: %d\t%d\t%d  M: %d\t%d\t%d", ax, ay, az, mx, my, mz);
  
  Serial.println(buf);
}
