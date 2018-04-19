/*
 * STM32GENERIC arduino extension sample
 * bitband (宏使用) demo  
 * bitband for m3/4 位域操作仅 m3/4 支持, 直接对位域地址读写，这是最快的位操作；
 * huaweiwx@sina.com 2017.12.26
 */


#if !(defined(STM32F0)||defined(STM32L0)||defined(STM32F7)||defined(STM32H7))
//use bidboud
# include "util/bitband.h"
#else
# error "BitBand unsuport this mcu!"
#endif

// the setup function runs once when you press reset or power the board
uint32_t ledaddr;  // save LED_BUILTIN bitband addr;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //  ledaddr = PIN_OUTADDR(LED_BUILTIN);     //get addr use macro
  ledaddr = BB_pinAdr(LED_BUILTIN, OUTPUT);  //get addr use functon
}

// the loop function runs over and over again forever
void loop() {
  MEM_ADDR(ledaddr) = 1;  /* bitband opration set high*/
  delay(500);
  MEM_ADDR(ledaddr) = 0; /* bitband opration setlow*/
  delay(500);
}