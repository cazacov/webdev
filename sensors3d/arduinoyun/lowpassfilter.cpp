#include "lowpassfilter.h"

#define LP_ALPHA 0.10

// Low pass filter

LowPassFilter::LowPassFilter()
{
  oldValue = 0.0;
}  


int LowPassFilter::filter(int newValue)
{
  oldValue = oldValue + LP_ALPHA * (newValue - oldValue);
  return oldValue;
}
