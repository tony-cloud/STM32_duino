/**  sram_test.ino   sram(sdram) test for this board:
      DISCOVERY_F746NG
      DISCOVERY_F429ZI
      ARMFLY_F407ZG
      HASEE_III_F103ZE
      ILLUMINATI_F407ZG
      REDBULL_V2_F103ZE
   Allocate ext ram, and write to Serial the results
*/

#include <stm32ExtRam.h>
STM32EXTRAM& extRAM = STM32EXTRAM::getInstance(); /* One instance only*/

#define led  LED_BUILTIN


void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  delay(200);

  uint32_t size = 960 * 1024;
  uint8_t* ptr = extRAM.malloc<uint8_t>(size);
  if (ptr) {
    Serial.print("malloc ");
    Serial.print(size);
    Serial.print(" ok!");
  } else {
    Serial.print("Error: cannot malloc ");
    Serial.print(size);
    Serial.print(" bytes!");
    return;
  }

  Serial.print("\nperused: ");
  Serial.println(extRAM.perused());

  Serial.print("test ptr baes adr read:");
  Serial.println((uint32_t)ptr, HEX);

  for (uint32_t i = 0; i < 16; i++) {
    ptr[i] = i;
  }

  for (uint32_t i = 0; i < 16; i++) {
    Serial.print(ptr[i], HEX);
    Serial.print(" ");
  }
  Serial.println("\nok");

  extRAM.free(ptr);
  Serial.print("\nperused: ");
  Serial.println(extRAM.perused());

  size = 1024 * 1024;
  ptr = extRAM.malloc<uint8_t>(size);
  if (ptr) {
    Serial.print("malloc ");
    Serial.print(size);
    Serial.print(" ok!");
  } else {
    Serial.print("Error: cannot malloc ");
    Serial.print(size);
    Serial.print(" bytes!");
    return;
  }

}

void loop() {
  delay(500);
  digitalToggle(led);
}

