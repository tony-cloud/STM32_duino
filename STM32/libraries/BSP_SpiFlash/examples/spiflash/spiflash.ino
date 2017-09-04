/**  sram_test.ino   sram(sdram) test for this board:
      DISCOVERY_F746NG
      DISCOVERY_F429ZI
      ARMFLY_F407ZG
      HASEE_III_F103ZE
      ILLUMINATI_F407ZG
      REDBULL_V2_F103ZE
      WAVESHARE_F746IG
   Allocate 256k ram, and write to Serial the results
*/
#include <BSP_SpiFlash.h>

#define led1 LED_BUILTIN

/* usage: 1 W25QXX  myFlash;        use spiconfig file define parameter
 *        2 W25QXX  myFlash(SPI1);  use SPI1
 *        3 W25QXX  myFlash(MOSI,MISO, SCK);  use SPI pindef
 * */
W25QXX  myFlash;
void setup() {
  pinMode(led1, OUTPUT);
  Serial.begin(115200);
  Serial.println("SPIFLASH ID:");
  delay(100);
//  myFlash.begin(PA4); //PA4 as  spiflash cs_pin
  myFlash.begin();      //default spiflash cs_pin
  uint32_t id = myFlash.jedecDeviceID();
  Serial.println(id, HEX);

  uint8_t buf[256];
  myFlash.read(buf, 0, 256);
  for (uint16_t i = 0; i < 256; i++) {
    Serial.print(buf[i], HEX);
    Serial.print("  ");
  }
  Serial.println("read ok!");
}

void loop() {
  digitalToggle(led1);
  delay(1000);
}

