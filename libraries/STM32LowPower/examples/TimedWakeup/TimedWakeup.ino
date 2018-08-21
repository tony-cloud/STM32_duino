/*
  TimedWakeup

  This sketch demonstrates the usage of RTC Internal Interrupts to wakeup a chip
  in deep sleep mode.

  In this sketch, the internal RTC will wake up the processor every second.

  This example code is in the public domain.
*/

#include "STM32LowPower.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("Wakeup a chip in deep sleep mode");
  
#if 0
  /* Increase the startup loop  for connection jlink or stlink debugger.
     Because in sleep mode, stlink or jlink disconnected to chip
  */
  Serial.println("Please input any key from serial to begin demo.........");
  while (!Serial.available()) {
    digitalToggle(LED_BUILTIN);
    delay(100);
  }
#else
  Serial.println("Press BUTTON while reboot into arduino upload mode");
  pinMode(BUTTON, INPUT);

  if ( digitalRead(BUTTON) == (BUTTON_MASK & 0x01)) {
    Serial.println("Nucleo can be upload now");
    while (1) {
      digitalToggle(LED_BUILTIN);
      delay(100);
    }
  }
#endif
  
  Serial.println("internal RTC will wake up the processor every second now");
  Serial.flush();
  
  // Configure low power
  LowPower.begin();
}

void loop() {
  digitalToggle(LED_BUILTIN);

/* selected onenof: */  
//  LowPower.idle(1* 1000);    /* 1 second*/
//  LowPower.sleep(1* 1000);   /* 1 second*/
  LowPower.deepSleep(1* 1000); /* 1 second*/
//  LowPower.shutdown(10*1000);  /* shutdown 10 second, the internal RTC will wake up(reboot) */
}
