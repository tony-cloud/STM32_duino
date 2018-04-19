/*
 * STM32GENERIC arduino extension sample
 * flash/sram var bitband(bit read/write)  template 
 * bitband for m3/4 位域操作仅 m3/4 支持, 直接对位域地址读写，这是最快的位操作；
 * huaweiwx@sina.com 2017.12.26
 */
 
#include "util/bitband.h"

/*BITBAND for M3/M4 only*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uint32_t test_var = 0;

// get test_var bitband ptr  
  volatile uint32_t* bbpvar = BB_sramVarPtr(test_var);
  
  for (uint32_t i = 0; i < 32; i++) { 
//  *bbpvar ++ =1;
    bbpvar[i] = 1;  //set var every bit to 1
    Serial.println(test_var, HEX);  //show it
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
