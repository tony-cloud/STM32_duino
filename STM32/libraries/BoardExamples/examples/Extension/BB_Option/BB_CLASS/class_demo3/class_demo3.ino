/*
 * STM32GENERIC arduino extension sample
 * bitband class BB_PIN oprator = and oprator () demo 
 * bitband for m3/4 位域操作仅 m3/4 支持, 直接对位域地址读写，这是最快的位操作；
 *          对 m0/m7，bitband class 调用 LL_PIN class 实现；
 * huaweiwx@sina.com 2017.12.26
 */
 
#include "util/bitband.h"

BB_PIN<LED_BUILTIN>led;
BB_PIN<BOTTON1>botton;

void setup() {
  // put your setup code here, to run once:
  led.mode(OUTPUT);
  botton.mode(INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  led = botton;  
}
