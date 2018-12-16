/*
  MEM2MEM.ino:  Memorey to memorey STM32DMA demo

  by  huaweiwx@sina.com 2018.7.25
*/

#include "stm32_dma.h"

STM32DMA<STM32DMA<>::MEMTOMEM>dma;
//STM32DMA<>dma;

#define TESTLEN  1024  /**/
uint16_t sour[TESTLEN], dis[TESTLEN];

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.println("DMA mentomen test....");
  Serial.flush();

  for (uint32_t i = 0; i < sizeof(sour) / sizeof(sour[0]); i++) sour[i] = i;

  dma.Init();
  if (dma.start((uint32_t *)sour, (uint32_t *)dis, sizeof(dis)) == HAL_OK) {
    for (uint32_t i = 0; i < sizeof(dis) / sizeof(dis[0]); i++) {
      Serial.print(dis[i], HEX); 
      if ((i & 0xf) == 0x0f)Serial.println();
      else Serial.print(" ");
    }
    Serial.println("dma test ok!");
  } else {
    Serial.println("!dma fault!");
  }
}

// the loop routine runs over and over again forever:
void loop() {
  digitalToggle(LED_BUILTIN);
  delay(500);
}

