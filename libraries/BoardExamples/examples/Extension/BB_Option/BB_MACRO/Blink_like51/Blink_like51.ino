/*
 * STM32GENERIC arduino extension sample
 * bitband macro(宏使用) demo 
 * bitband for m3/4 位域操作仅 m3/4 支持, 直接对位域地址读写，这是最快的位操作；
 * huaweiwx@sina.com 2017.12.26
 */

#if !(defined(STM32F0)||defined(STM32L0)||defined(STM32F7)||defined(STM32H7))
//use bidboud
# include "util/bitband.h"
#else
# error "BitBand unsuport this mcu!"
#endif

//#define LED PDout(2)            /*LED_BUILTIN on PD2*/
#define LED PINout(LED_BUILTIN)    /*LED_BUILTIN bitband out*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); 
}


// the loop function runs over and over again forever
void loop() { 
  LED = 1;  /* bitband opration set high*/
  delay(500);
  LED = 0;  /* bitband opration setlow*/
  delay(500);
}
