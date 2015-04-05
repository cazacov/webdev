
#ifndef _FILTER_h
#define _FILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Filter
{
 private:
  int buf[3]; 
  byte ptr;
 public:
  Filter(); 
  int filter(int v1);
};
#endif
