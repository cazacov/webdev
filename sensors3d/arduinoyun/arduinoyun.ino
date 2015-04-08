#include <Wire.h>

#include "sensors.h"
#include "lowpassfilter.h"

Sensors sensors(-125, -177, -356, 6160.0/616, 6160.0/527, 6160.0/458);

// Median filters
LowPassFilter fax;
LowPassFilter fay;
LowPassFilter faz;
LowPassFilter fmx;
LowPassFilter fmy;
LowPassFilter fmz;

void waitForNodeServer();

void setup(void) 
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial1.begin(115200); // Set Linux baud baud.
  // Logging
  Serial.begin(115200);
  sensors.init();  
  waitForNodeServer();
}

void loop(void) 
{
  char buf[80];
  int ax,ay,az, mx,my,mz;
  

    sensors.readAccelerometer(ax, ay, az);
    sensors.readMagnetometer(mx, my, mz);  
  
    ax = fax.filter(ax);
    ay = fay.filter(ay);  
    az = faz.filter(az);    
    mx = fmx.filter(mx);
    my = fmy.filter(my);  
    mz = fmz.filter(mz);    
  
    sprintf(buf, "%d,%d,%d,%d,%d,%d@", ax, ay, az, mx, my, mz);
    Serial1.println(buf);
    delay(40);
}

void waitForNodeServer()
{
  // Wait until 'n' appers 10 times in the input stream
  
  bool serverIsListening = false;
  int c;
  int charCount = 0;
  
  while (charCount < 10)
  {
    c = Serial1.read();                 // read from UART
    if (c != -1) {                      // got anything?
      Serial.write(c);                  // write to USB-CDC
    }
    if (c == 'n')
    {
      charCount++;
      Serial.println(charCount);
      if (charCount == 10)  // 10 times 'n' is a signal to start sending sensor data to the server
      {
        serverIsListening = true;

        Serial.println("Got start signal from the server");
        delay(100);

        // clear input buffer
        while (c != -1)
          c = Serial1.read();

        digitalWrite(13, HIGH);  // Make end of waiting visible
        
        return;
      }        
    }
    else {
      charCount = 0;      
    }
  }
}
