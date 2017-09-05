/* USB drive based on internal flash
 * Select USB: Mass Storage from the menu
 * EXPERIMENTAL, for testing purposes.
 * When writing, use eject drive, or the filesystem may get corrupted. In that case, use:
 *   chkdsk <drive> /f
 * Connect to USB. Upload files. Eject drive, Disconnect. Reconnect. Files should be there.
 * Create a config.txt in, and write 1/2/3 into it. The leds will light up accordingly
 * modify for C8T6  by huaweiwx@sina.com
 */
 
#include "Flash_STM32.h"

//check Environmental
#ifndef MENU_USB_MASS_STORAGE
#error   "You must select USB: Mass Storage from the menu!"  //必须在菜单上 选择 USB: Mass Storage
#endif

#define LED  LED_BUILTIN      // same as LED_BUILTIN

#ifdef  LED1_BUILTIN
#define LED1 LED1_BUILTIN
#endif

#define FLASHDRIVE_SIZE    1*1024 // Half of one flash page is about OK for drive size
#define FLASHDIVE_BLOCKS   64*FLASHDRIVE_SIZE/512	/*64k*/

//2 x 32KB flash pages (see reference manual / flash module organization)
STM32EmbeddedFlashBlock block0(FLASH_BASE + 64 * 1024, 32 * 1024);  //64~96k
STM32EmbeddedFlashBlock block1(FLASH_BASE + 96 * 1024, 32 * 1024);  //96~128k

// combine them into one virtual storage of 512 bytes
FlashVariables<512> storageBackend(&block0, &block1);


// SdFat interface, so we can access it from the microcontroller
FlashBlockFat fat(&storageBackend);


// USB interface so we can access it through USB
FlashBlockDevice flashBlockDevice(FLASHDIVE_BLOCKS, &storageBackend);

// When we open the first time, and is not formatted, format it
void formatListener() {
    formatFat12(&flashBlockDevice, FLASHDIVE_BLOCKS);
}

//Called by USB subsystem
BlockDevice *getMassStorage() {
    storageBackend.setFormatListener(formatListener);

    //If the drive appears unformatted, try this (should not be needed):
    //storageBackend.format();

    return &flashBlockDevice;
}

void setup() {
    Serial.begin(115200);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
	
#ifdef  LED1
    pinMode(LED1, OUTPUT);
    digitalWrite(LED1, HIGH);
#endif

    delay(1000);

    fat.begin();
}

void loop() {
    delay(10);

    // Needed, or SdFat will not know about changes from USB drive
    fat.cacheClear();


    File f = fat.open("config.txt", FILE_READ);
    if (!f) {
        return;
    }

    char c = f.read();
    Serial.println(c);
    switch(c) {
        case '1':
            digitalWrite(LED, LOW);
#ifdef  LED1
            digitalWrite(LED1, HIGH);
#endif
            break;
        case '2':
            digitalWrite(LED, HIGH);
#ifdef  LED1
            digitalWrite(LED1, LOW);
#endif
            break;
        case '3':
            digitalWrite(LED, LOW);
#ifdef  LED1
            digitalWrite(LED1, LOW);
#endif
            break;
        default:
            digitalWrite(LED, HIGH);
#ifdef  LED1
            digitalWrite(LED1, HIGH);
#endif
            break;
    }
    f.close();

    //
    //delay(1000);
}
