//
//  at24cxx_rw_wire.ino
//
//  huawei huaweiwx@sina.com 2017.2.21
//


#include "WireSoft.h"
#include "at24cxx.h"
#include <Streaming.h> /*for Serial << */

//my vct6 board config, check and fix me

#define EE_SDA     AT24CXX_SDA
#define EE_SCL     AT24CXX_SCL
#define EE_TYPE    AT24C02

#define   EE_DISK0 0x50    //Address of AT24LC512 A2A1A0=000

EXTEEPROM  mywire(EE_SDA, EE_SCL);

void setup() {
  Serial.begin(115200);
  Serial.println("\nAT24CXX RW");
  mywire.begin(EE_DISK0, EE_TYPE); //
  
  //write all eeprom with page number; run one times only
//  for (uint16_t i = 0; i < 256; i++) {
//    for (uint16_t j = 0; j < 256; j++) {
//       if ((i * 256 + j) <=  EE_TYPE)
//          mywire.write(i * 256 + j, j);
//      else return;
//    }
//  }
  
}

void loop() {
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial << _HEX(mywire.read( i * 16 + j)) << "  ";
    }
    Serial << "\n";
  }
  Serial << "disk @000 ok\n\n";
  delay(5000);           // wait 5 seconds for next scan
}

