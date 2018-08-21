/*
  AdvancedTimedWakeup

  This sketch demonstrates the usage of Internal RTC alarm Interrupts to wakeup a chip in deep sleep mode.

  In this sketch:
  - RTC date and time are configured.
  - Alarm is set to wake up the processor each 'atime' and called a custom alarm callback
  which increment a value and reload alarm with 'atime' offset.

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
#include <STM32RTC.h>

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

// Time in second between blink
static uint32_t atime = 1;

// Declare it volatile since it's incremented inside an interrupt
volatile int alarmMatch_counter = 0;

// Variables for RTC configurations
static byte seconds = 0;
static byte minutes = 0;
static byte hours = 0;

static byte weekDay = 1;
static byte day = 1;
static byte month = 1;
static byte year = 18;

void setup() {
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(weekDay, day, month, year);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(1000); /* wait for serial ready */
  Serial.println("AlarmTimer Wakeup a chip in deep sleep mode");
  
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
  
  // Configure low power
  LowPower.begin();
  LowPower.enableWakeupFrom(&rtc, alarmMatch, &atime);

  // Configure first alarm in 2 second then it will be done in the rtc callback
  rtc.setAlarmEpoch( rtc.getEpoch() + 3 );
}

void loop() {
  Serial.print("Alarm Match: ");
  Serial.print(alarmMatch_counter);
  Serial.println(" times.");
  Serial.flush();
  
/* selected onenof: */    
//  LowPower.idle(); 
//  LowPower.sleep(); 
  LowPower.deepSleep(); 
  
  digitalToggle(LED_BUILTIN);
}

void alarmMatch(void* data)
{
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
  uint32_t sec = 1;
  if(data != NULL) {
    sec = *(uint32_t*)data;
    // Minimum is 1 second
    if (sec == 0){
      sec = 1;
    }
  }
  alarmMatch_counter++;
  rtc.setAlarmEpoch( rtc.getEpoch() + sec);
}

