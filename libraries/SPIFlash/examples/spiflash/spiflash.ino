/**  spiflash.ino  spiflash test for this board:
      HASEE_III_F103ZE
      ILLUMINATI_F407ZG
      REDBULL_V2_F103ZE
*/
#include <Streaming.h>

#ifndef USE_SOFT_SPIFLASH
//#define  USE_SOFT_SPIFLASH
#endif

#include <SpiFlash.h>
/* usage: 1 SPIFLASH  myFlash;        use spiconfig file define parameter
          2 SPIFLASH  myFlash(SPI1);  use SPI1
          3 SPIFLASH  myFlash(SPIFLASH_MOSI,SPIFLASH_MISO, SPIFLASH_SCK);  use SPI pindef
          4 SOFT_SPIFLASH <SPIFLASH_MOSI, SPIFLASH_MISO, SPIFLASH_SCK, SPIFLASH_CS> myFlash
*/
#ifdef USE_SOFT_SPIFLASH
SOFT_SPIFLASH <SPIFLASH_MOSI, SPIFLASH_MISO, SPIFLASH_SCK, SPIFLASH_CS> myFlash;  /*use software spi*/
#else
SPIFLASH  myFlash;  /*use hardware spi*/
#endif

/*class DigitalPin define in util/digitalIO.h & SpiFlash.h included it*/
DigitalPin<LED_BUILTIN>led1;

void setup() {
  led1.mode(OUTPUT);
  Serial.begin(115200);
  delay(1000);

  Serial.println("Press any key to begin.....");
  while (!Serial.available()) {
    led1.toggle();
    delay(100);
  } ; //wait for usb_serial input a char;

  Serial.println("SPIFLASH ID:");

  //  myFlash.begin(PA4); //PA4 as  spiflash cs_pin
  myFlash.begin();       //default spiflash cs_pin

  uint32_t id = myFlash.readID();
  Serial << "DeviceID:" << _HEX(id) << "\n";
  Serial << "capacity:" << myFlash.capacity() / 1024 << " k\n";

  uint8_t buf[256];
  myFlash.read(buf, 0, 256);
  for (uint16_t i = 0; i < 256; i++) {
    Serial << _HEX(buf[i]) << "  ";
  }
  Serial.println("\nread ok!");
}

void loop() {
  led1.toggle();
  delay(1000);
}


