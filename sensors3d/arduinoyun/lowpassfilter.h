
#ifndef _LOWPASSFILTER_h
#define _LOWPASSFILTER_h

class LowPassFilter
{
 private:
  float oldValue;
 public:
  LowPassFilter(); 
  int filter(int newValue);
};
#endif
