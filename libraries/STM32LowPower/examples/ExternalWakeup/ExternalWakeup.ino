/*
  ExternalWakeup

  This sketch demonstrates the usage of External Interrupts (on pins) to wakeup
  a chip in sleep mode. Sleep modes allow a significant drop in the power usage
  of a board while it does nothing waiting for an event to happen.
  Battery powered application can take advantage of these modes to enhance
  battery life significantly.

  In this sketch, pressing a pushbutton attached to wkpin will wake up the board.

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

// Blink sequence number
// Declare it volatile since it's incremented inside an interrupt
volatile int repetitions = 1;

// wkpin used to trigger a wakeup
#define wkpin BUTTON        /*default USER BUTTON*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  //  Set wkpin as INPUT(PU/PD) to avoid spurious wakeup selected oneof:
  pinMode(wkpin, INPUT);                //nucleo userbutton have a 4.7k pullup resistance
  //  pinMode(wkpin, INPUT_PULLDOWN);   //for on is highlever button without resistance
  //  pinMode(wkpin, INPUT_PULLUP);     //for on is lowlelver button without resistance

  Serial.begin(115200);
  delay(1000); /* wait for serial ready */
  Serial.println("Button interrupt Wakeup a chip in deep sleep mode");

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
  /* Increase the startup loop  for connection jlink or stlink debugger.
     Because in sleep mode, stlink or jlink disconnected to chip
  */
  Serial.println("Press BUTTON while reboot into arduino upload mode");
  if ( digitalRead(BUTTON) == (BUTTON_MASK & 0x01)) {
    Serial.println("Nucleo can be  upload now");
    while (1) {
      digitalToggle(LED_BUILTIN);
      delay(100);
    }
  }
#endif

  Serial.flush();
  // Configure low power
  LowPower.begin();
  // Attach a wakeup interrupt on wkpin, calling repetitionsIncrease when the device is woken up
  LowPower.attachInterruptWakeup(wkpin, repetitionsIncrease, RISING);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalToggle(LED_BUILTIN);
    delay(200);
  }
  // Triggers an infinite sleep (the device will be woken up only by the registered wakeup sources)
  // The power consumption of the chip will drop consistently
  Serial.println("deepSleep now,Press BUTTON wakeup........");
  Serial.flush();/*before sleep,wait output comlated*/

  /* selected onenof lowpower mode: */
  //  LowPower.idle();    /*all gpio pin can wakeup from idle and sleep*/
  //  LowPower.sleep();
  LowPower.deepSleep();  /* If the Gpio pin is a Wake up pin activate it for deepSleep (standby stm32) */
  //  LowPower.shutdown();  /* wkpin is SYS_WKUPx only. exp:PA0 */

  //if shutdown, wakeup to reboot and not run to here
  Serial.print(repetitions); /*all gpio pin can wakeup from idle and sleep*/
  Serial.println("  wakeup."); /*all gpio pin can wakeup from idle and sleep*/
}

void repetitionsIncrease() {
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
  repetitions ++;
}
