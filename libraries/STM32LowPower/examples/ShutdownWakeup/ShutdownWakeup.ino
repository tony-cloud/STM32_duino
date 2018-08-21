/*
  ShutdownWakeup.ino
  This sketch demonstrates the usage of Internal Interrupts to wakeup a chip  in shutdown mode.
  In this sketch, after mcu shutdown 10 second , the internal RTC will wake up(reboot) the processor.

  This example code is in the public domain.
  
  Note:
  * **Idle mode**: low wake-up latency (µs range) (e.g. ARM WFI). Memories and
      voltage supplies are retained. Minimal power saving mainly on the core itself.
  * **sleep mode**: low wake-up latency (µs range) (e.g. ARM WFI), Memories and
      voltage supplies are retained. Minimal power saving mainly on the core itself but
      higher than idle mode.

  * **deep sleep mode**: medium latency (ms range), clocks are gated to reduced. Memories
      and voltage supplies are retained. If supported, Peripherals wake-up is possible (UART, I2C ...).

  * **shutdown mode**: high wake-up latency (posible hundereds of ms or second
      timeframe), voltage supplies are cut except always-on domain, memory content
      are lost and system basically reboots.
*/

#include "STM32LowPower.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);
  Serial.println("Wakeup a chip in Shutdown mode");

#if 0
  /* Increase the startup loop  for connection jlink or stlink debugger.
     Because in sleep mode, stlink or jlink disconnected to chip
  */
  Serial.println("Please input any key begin demo.........");
  while (!Serial.available()) {
    digitalToggle(LED_BUILTIN);
    delay(100);
  }
#else
  Serial.println("Press BUTTON while reboot into arduino upload mode");
  pinMode(BUTTON, INPUT);

  if ( digitalRead(BUTTON) == (BUTTON_MASK & 0x01)) {
    Serial.println("Nucleo can be  upload now");
    while (1) {
      digitalToggle(LED_BUILTIN);
      delay(100);
    }
  }
#endif
  Serial.println("internal RTC will wake up the processor after 10 second");
  Serial.flush(); /* Before into low power,wait serial output complated */

  // Configure low power
  LowPower.begin();
}

void loop() {
  LowPower.shutdown(10*1000); /* shutdown 10 second, the internal RTC will wake up(reboot) */
}
