/*
  SerialWakeup

  This sketch demonstrates the usage of Serial(SerialLPUART) Interrupts to wakeup a chip  in sleep  mode.

  This sketch is compatible only with board supporting uart peripheral in
  stop mode.

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

// Declare it volatile since it's incremented inside an interrupt
volatile int wakeup_counter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000); /* wait for Serial ready */
  
  Serial.println("Sleep wakeup from Serial demo");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

#if 0
  /* Increase the startup loop  for connection jlink or stlink debugger.
     Because in sleep mode, stlink or jlink disconnected to chip
  */
  Serial.println("Please input any key from serial to begin demo .........");
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

  Serial.flush();
  // Configure low power
  LowPower.begin();
  // Enable UART in Low Power mode wakeup source
  LowPower.enableWakeupFrom(&Serial, SerialWakeup);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
  // Triggers an infinite deep sleep
  // (the device will be woken up only by the registered wakeup sources)
  // The power consumption of the chip will drop consistently
  Serial.println("Start sleep wakeup from Serial, and press any key from Serial wakeup the chip......");
  Serial.flush();
  
  LowPower.sleep();
  Serial.print(wakeup_counter);
  Serial.println(" wake up");

  // Empty Serial Rx
  while (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);
  }
  Serial.println();
}

void SerialWakeup() {
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables
  // which will be used in the loop)
  // Remember to avoid calling delay() and long running functions
  // since this functions executes in interrupt context
  wakeup_counter++;
}
