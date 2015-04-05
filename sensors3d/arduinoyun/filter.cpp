#include "filter.h"

Filter::Filter()
{
  buf[0] = buf[1] = buf[2];
  ptr = 0;
}  

int Filter::filter(int newValue)
{
  buf[ptr++] = newValue;
  if (ptr == 3)
  {
    ptr = 0;
  }
  
  int v1 = buf[0];
  int v2 = buf[1];
  int v3 = buf[2]; 
  
  if (v1 <= v2 && v2 <= v3)  return v2;
  if (v1 <= v3 && v3 <= v2)  return v3;  
  if (v2 <= v1 && v1 <= v3)  return v1;
  if (v2 <= v3 && v3 <= v1)  return v3;  
  if (v3 <= v1 && v1 <= v2)  return v1;
  if (v3 <= v2 && v2 <= v1)  return v2;  
}
