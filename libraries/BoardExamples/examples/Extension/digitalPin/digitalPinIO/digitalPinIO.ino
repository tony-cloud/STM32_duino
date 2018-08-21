/* digitalPin.ino  DigitalPin class Template 
 * huaweiwx@sina.com  2017.12.28
 */
#include "util/digitalPin.h"

DigitalPin<LED_BUILTIN>led;
DigitalPin<BUTTON1>butt1;

bool state=false;

void setup()
{
  Serial.begin(115200);
  Serial.println("Blink use DigitalPin class");
  
  led.mode(OUTPUT);
  butt1.mode(INPUT);
}

void loop()                    
{
    led = butt1;  
}
