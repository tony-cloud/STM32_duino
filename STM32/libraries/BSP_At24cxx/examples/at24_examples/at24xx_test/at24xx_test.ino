//  at24cxx_rw_wire.ino
//  huaweiwx@sina.com 2017.2.21
#include <BSP_At24cxx.h>

#define LED  LED_BUILTIN

AT24XX EEPROM(AT24C02);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  //EEPROM.begin();    //defaul chip addr A2A1A0 = 000;
  //EEPROM.begin(0x03) //A2A1A0 =011

  while (!Serial.available()) { //wait for usb_serial available;
    digitalToggle(LED);
    delay(1000);
  }

  if (EEPROM.begin())
    Serial << "eeprom init err!  dev:24C " << EEPROM.pdata->dev << "  at adr 0x" << _HEX(EEPROM.pdata->devAdr) << "\n";
  else if (EEPROM.pdata->dev <  AT24C16)
    Serial << "eeprom init ok    dev:24C0" << EEPROM.pdata->dev << "  at adr 0x" << _HEX(EEPROM.pdata->devAdr) << "\n";
  else
    Serial << "eeprom init ok    dev:24C" << EEPROM.pdata->dev << "  at adr 0x" << _HEX(EEPROM.pdata->devAdr) << "\n";

  /*
    for (uint16_t i = 0; i < 16; i++) {
      EEPROM.writeOneByte((uint16_t)i, (uint8_t)i);
    }
  */
  
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial << _HEX(EEPROM.readOneByte(i * 16 + j)) << " ";
    }
    Serial << "\n";
  }
}


void loop() {
  digitalToggle(LED);
  delay(1000);
  // Insert background code here
}


