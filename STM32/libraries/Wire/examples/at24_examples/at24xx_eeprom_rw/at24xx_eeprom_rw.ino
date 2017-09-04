//
//  at24cxx_rw_wire.ino
//  
//  huawei huaweiwx@sina.com 2017.2.21
//


#include <at24cxx.h>

//my vct6 board config, check and fix me 
#define EE_SCL PE5 //PB6
#define EE_SDA PE6 //PB7
#define   EE_DISK0 0x50    //Address of AT24LC512 A2A1A0=000
//#define EE_DISK1 0x51    //Address of AT24LCXX  A2A1A0=001  not found
#define EE_DISK2 0x52      //Address of FM24LC04  A2A1  =01x  page0
#define EE_DISK3 0x53      //Address of FM24LC04  A2A1  =01x  page1


EEPROM  mywire(EE_SCL, EE_SDA, 200);

void setup() {
  Serial1.begin(115200);
  Serial1.println("\nAT24CXX RW");
/*  
//write all eeprom with page number; run one times only
  mywire.begin(EE_DISK0,AT24C512);  //check and fix me 
  for (uint16_t i = 0; i < 256; i++){
    for(uint16_t j=0;j<256;j++){
	    if ((i*256+j)<=AT24C512)
            mywire.write(i*256+j,i);
		else return;	
	}	
  }
*/  
}

void loop() {
#ifdef EE_DISK0
  mywire.begin(EE_DISK0,AT24C512);
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(mywire.read( i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @000 ok\n\n";
#endif

#ifdef EE_DISK1
  mywire.begin(EE_DISK1,AT24C02);
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(mywire.read( i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @001 ok\n\n";
#endif

#ifdef EE_DISK2
  mywire.begin(EE_DISK2,AT24C02);
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(mywire.read( i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @010 ok\n\n";
#endif

#ifdef EE_DISK3
  mywire.begin(EE_DISK3,AT24C02);
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
       Serial1 << _HEX(mywire.read( i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "\ndisk @011 ok\n";
#endif
  delay(5000);           // wait 5 seconds for next scan
}

