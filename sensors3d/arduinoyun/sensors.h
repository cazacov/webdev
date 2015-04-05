
#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Wire.h>

class Sensors
{
 private:
   int cx;
   int cy;
   int cz;
   float scaleX;
   float scaleY;
   float scaleZ;   
  void initAccelerometer(void);
  void initMagnetometer(void);
  void writeTo(int device, byte address, byte val);
 public:
  Sensors(int pxc = 0, int pcy = 0, int pcz = 0, float sx = 1.0, float sy = 1.0, float sz = 1.0);
  void init(void);
  void readAccelerometer(int &x, int &y, int &z);
  void readMagnetometer(int &x, int &y, int &z);  
};
#endif

