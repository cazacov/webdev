
#ifndef _MEDIANFILTER_h
#define _MEDIANFILTER_h

#define FILTER_SIZE 5

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class MedianFilter
{
 private:
  int buf[FILTER_SIZE]; 
  byte ptr;
  void sort(int* arr, int arraySize);
 public:
  MedianFilter(); 
  int filter(int newValue);
};
#endif
