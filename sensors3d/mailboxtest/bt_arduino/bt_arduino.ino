#include <Bridge.h>

unsigned long timer;
unsigned long counter = 0L;

void setup()
{
    Bridge.begin();     // this launches /usr/bin/run-bride on Linino
    timer = millis();
}

void loop()
{
    /* Every 200ms: */

    if (millis() - timer > 200) {
        timer = millis();
        Bridge.put("s", String(counter++));
    }
}
