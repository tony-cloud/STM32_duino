/* BB/LL class EXIT template
   huaweiwx@sina.com 2017.12.26
*/
#include "util/bitband.h"

BB_PIN led(LED_BUILTIN);
BB_PIN pbIn(BUTTON);

void setup()
{
  led.mode(OUTPUT);
  pbIn.mode(INPUT);

  pbIn.attach(pbIncallback, CHANGE);
}

void loop() {}

void pbIncallback()
{
  led = pbIn;
}
