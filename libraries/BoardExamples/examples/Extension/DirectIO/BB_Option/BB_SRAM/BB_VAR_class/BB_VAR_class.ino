/*
   BB_VAR_class.ino
   STM32GENERIC arduino extension sample
   flash/sram var bitband(bit read/write) class template
   bitband for m3/4 位域操作仅 m3/4 支持, 直接对位域地址读写，这是最快的位操作；
   huaweiwx@sina.com 2017.12.26
*/

#include "util/bitband.h"

/*BITBAND for M3/M4 only*/
BB_VAR<uint32_t>status;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);

  status = 0;
  
  for (uint32_t i = 0; i < 32; i++) {
    status.bit[i] = 1;  //set var every bit to 1
    Serial.println(status, HEX);  //show it
  }
}

void loop() {
  // put your main code here, to run repeatedly:
//  status.index[0] = 0;
}
