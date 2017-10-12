#include <Flash_STM32.h>
#include <FlashBlockFat.h>

#if defined(STM32F103C8)||defined(STM32F103CB)||defined(STM32F103RB)|| defined(STM32L152C8)
#   define FLASH_LENTH 128
#elif defined(STM32F103VC)||defined(STM32F103VE)||defined(STM32F103ZE)||defined(STM32F103RE)||defined(STM32F103RC)\
      ||defined(STM32F407VE)||defined(STM32F407ZE)
#   define  FLASH_LENTH   512	  
#elif defined(STM32F407VG)||defined(STM32F407ZG)||defined(STM32F207ZG)
#   define  FLASH_LENTH   1024	  
#endif


#if defined(STM32F103C8)||defined(STM32F103CB)||defined(STM32F103RB)||defined(STM32L152C8)\
    ||defined(STM32F103RC)||defined(STM32F103VC)||defined(STM32F103VE)||defined(STM32F103ZE)||defined(STM32F103RE)
#	define FLASHDIVE_BLOCKS   FLASHDISK_SIZE*1024/512
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE)   * 1024, (FLASHDISK_SIZE/2) * 1024);  //64~96k
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE/2) * 1024, (FLASHDISK_SIZE/2) * 1024);  //96~128k
#elif defined(STM32F407VE)||defined(STM32F407ZE)
#	define FLASHDIVE_BLOCKS   FLASHDISK_SIZE*1024/512	/*256k*/
//2 x 128KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE)   * 1024,  (FLASHDISK_SIZE/2) * 1024);
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE/2) * 1024,  (FLASHDISK_SIZE/2) * 1024);
#elif defined(STM32F407VG)||defined(STM32F407ZG)||defined(STM32F207ZG)
#	define FLASHDIVE_BLOCKS   8*HALFPAGE_SIZE/512	/*512k*/
//4 x 128KB flash pages (see reference manual / flash module organization)
	STM32EmbeddedFlashBlock block0(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE)   * 1024,  (FLASHDISK_SIZE/2) * 1024);
	STM32EmbeddedFlashBlock block1(FLASH_BASE + (FLASH_LENTH-FLASHDISK_SIZE/2) * 1024,  (FLASHDISK_SIZE/2) * 1024);
#  else
	
#  error "undef this chip,please add me"
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
