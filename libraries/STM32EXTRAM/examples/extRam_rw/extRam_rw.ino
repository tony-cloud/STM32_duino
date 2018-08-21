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
STM32EXTRAM& extRAM = STM32EXTRAM::getInstance();

#define led LED_BUILTIN

uint32_t size;
uint32_t data;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  size = extRAM.getRamByteLength() / sizeof(data);
  delay(200);
}

void loop() {
  Serial.print("EXTRAM SIZE: 0x");
  Serial.println(extRAM.getRamByteLength(), HEX);
  uint32_t start = millis();

  uint32_t sum = 0;
  uint32_t sum_check = 0;

  for (uint32_t i = 0; i < size; i++) {
    data = i;
    sum += i;
    extRAM.writeData(i * sizeof(data), &data, 1) ;
  }

  Serial.print("Write time: ");
  Serial.print(millis() - start);
  Serial.println(" ms");
  start = millis();

  for (uint32_t i = 0; i < size; i++) {
    extRAM.readData(i * sizeof(data), &data, 1) ;
    sum_check += data;
  }

  Serial.print("Read time: ");
  Serial.print(millis() - start);
  Serial.println(" ms");

  Serial.print("Checksum should be:");
  Serial.println(sum);
  Serial.print("Checksum calculated:");
  Serial.println(sum_check);

  if (sum == sum_check) {
    Serial.print("EXTRAM is working with buffer size: ");
    Serial.println(size * sizeof(data));
  } else {
    Serial.println("!!! EXTRAM NOT WORKING !!!");
    while(1);
  }

  Serial.print("test ptr baes adr read:");
  uint32_t* ptr;
  ptr = extRAM.getRamBaseAddress<uint32_t>();
  Serial.println((uint32_t)ptr, HEX);
  for (uint32_t i = 0; i < 16; i++) {
    Serial.print(*ptr++, HEX);
    Serial.print(" ");
  }

  Serial.println("\n----------------------------------------");

  delay(5000);
  digitalToggle(led);
}

