#include "medianfilter.h"

// Median filter

MedianFilter::MedianFilter()
{
  memset(buf, 0, sizeof(buf)); 
  ptr = 0;
}  

// Straightforward bubble sort
void MedianFilter::sort(int* array, int arraySize)
{
  bool doSort = true;
  
  while(doSort)
  {
    doSort = false;
    int* first = array;
    int* second = array+1;    
    for (int i = 0; i < arraySize - 1; i++)
    {
      if (*first > *second)
      {
        int t = *second;
        *second = *first;
        *first = t;
        doSort = true;
      }
      first++;
      second++;
    }
  }
}

int MedianFilter::filter(int newValue)
{
  buf[ptr++] = newValue;
  if (ptr == FILTER_SIZE)
  {
    ptr = 0;
  }
  
  int sbuf[FILTER_SIZE];
  memcpy(sbuf, buf, sizeof(buf));
  sort(sbuf, FILTER_SIZE);
  
  return sbuf[FILTER_SIZE /2];
}
