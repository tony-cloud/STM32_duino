#include <Arduino.h>
#include <Flash_STM32.h>
#include <FlashBlockFat.h>

#ifndef FLASHDISK_SIZE
#  if defined(STM32F103C8)||defined(STM32F103CB)||defined(STM32F103RB)
#    define FLASHDISK_SIZE     64                /* 64*/  
#  elif  defined(STM32F103VC)||defined(STM32F103VE)||defined(STM32F103ZE)||defined(STM32F103RE)||defined(STM32F103RC)
#    define FLASHDISK_SIZE     256                /* 256k*/  
#  elif defined(STM32F407VE)||defined(STM32F407ZE)
#    define FLASHDISK_SIZE     256                /* 256k*/  
#  elif defined(STM32F407VG)||defined(STM32F407ZG)
#    define FLASHDISK_SIZE     512                /* 64k*/  
#  endif
#endif


#if defined(STM32F103C8)||defined(STM32F103CB)||defined(STM32F103RB)
#	define HALFPAGE_SIZE      FLASH_PAGE_SIZE/2 // Half of one flash page is about OK for drive size 0x400
#	define FLASHDIVE_BLOCKS   FLASHDISK_SIZE*HALFPAGE_SIZE/512	/*64k*/

//2 x 32KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (128-FLASHDISK_SIZE)   * 1024, (FLASHDISK_SIZE/2) * 1024);  //64~96k
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (128-FLASHDISK_SIZE/2) * 1024, (FLASHDISK_SIZE/2) * 1024);  //96~128k
 
#elif  defined(STM32F103VC)||defined(STM32F103VE)||defined(STM32F103ZE)||defined(STM32F103RE)||defined(STM32F103RC)
#	define HALFPAGE_SIZE      FLASH_PAGE_SIZE/2 // Half of one flash page is about OK for drive size 0x800
#	define FLASHDIVE_BLOCKS   LASHDISK_SIZE*HALFPAGE_SIZE/512	/*128k x2*/

//2 x 128KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (512-FLASHDISK_SIZE)   * 1024, (FLASHDISK_SIZE/2) * 1024);  //256~384k
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (128-FLASHDISK_SIZE/2) * 1024, (FLASHDISK_SIZE/2) * 1024);  //384~512k

#elif defined(STM32F407VE)||defined(STM32F407ZE)
#	define HALFPAGE_SIZE      64*1024 // Half of one flash page is about OK for drive size
#	define FLASHDIVE_BLOCKS   4*HALFPAGE_SIZE/512	/*256k*/

//2 x 128KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (512-FLASHDISK_SIZE)   * 1024,  (FLASHDISK_SIZE/2) * 1024);
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (512-FLASHDISK_SIZE/2) * 1024,  (FLASHDISK_SIZE/2) * 1024);
#elif defined(STM32F407VG)||defined(STM32F407ZG)
//#   define FLASHDISK_SIZE     512                /* 64k*/  
#	define HALFPAGE_SIZE    64*1024 // Half of one flash page is about OK for drive size
#	define FLASHDIVE_BLOCKS   8*HALFPAGE_SIZE/512	/*512k*/

//4 x 128KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (1024-FLASHDISK_SIZE)   * 1024,  (FLASHDISK_SIZE/2) * 1024);
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (1024-FLASHDISK_SIZE/2) * 1024,  (FLASHDISK_SIZE/2) * 1024);
#endif


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
