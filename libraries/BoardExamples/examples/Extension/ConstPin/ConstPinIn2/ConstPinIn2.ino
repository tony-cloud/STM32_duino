/*  The class __ConstPin define in file stm32_pin_list.h
 *   and operators ">>" and  "<<" were be overloaded in file stm32_gpio.h.
 *	
 *   huaweiwx@sina.com 2018.2.1
 */

void setup() {
  //  put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(BUTTON,INPUT);
}

void loop() {
  static uint8_t status;
  BUTTON >> status;   
  LED_BUILTIN << status;
}
