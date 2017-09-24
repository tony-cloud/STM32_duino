/* USB Mass Storage/MSC_CDC Composite drive based on internal flash,
   Select USB: Mass Storage or MSC_CDC Composite from the menu
   EXPERIMENTAL, for testing purposes.
   When writing, use eject drive, or the filesystem may get corrupted. In that case, use:
     chkdsk <drive> /f
   Connect to USB. Upload files. Eject drive, Disconnect. Reconnect. Files should be there.
   Create a config.txt in, and write 1/2/3 into it. The leds will light up accordingly
   
   if Select Serial Communication:SerialUSB from the menu, output message by USB CDC
   modify for f1/4  by huaweiwx@sina.com
*/

#include <FlashBlockFat.h>

#define LED  LED_BUILTIN      // same as LED_BUILTIN

// SdFat interface, so we can access it from the microcontroller
extern FlashBlockFat fat;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(1000);
  fat.begin();
}

void loop() {
  delay(1000);
  // Needed, or SdFat will not know about changes from USB drive
  fat.cacheClear();

  File f = fat.open("config.txt", FILE_READ);
  if (!f) {
    return;
  }

  char c = f.read();
  Serial.print("c= ");
  Serial.println(c);
  switch (c) {
    case '1':
      digitalWrite(LED, LOW);
      break;
    case '2':
      digitalWrite(LED, HIGH);
      break;
    case '3':
      digitalWrite(LED, LOW);
      break;
    default:
      digitalWrite(LED, HIGH);
      break;
  }
  f.close();
}
