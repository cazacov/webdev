
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
  void initAccelerometer(void);
  void initMagnetometer(void);
  void writeTo(int device, byte address, byte val);
 public:
  void init(void);
  void readAccelerometer(int &x, int &y, int &z);
  void readMagnetometer(int &x, int &y, int &z);  
};
#endif

