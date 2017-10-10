
#include <Flash_STM32.h>
#include <FlashBlockFat.h>


#ifndef SPIFLASHDISK_SIZE
#  define SPIFLASHDISK_SIZE     ((uint32_t)512)                /*W25X40 512k*/  
#endif

#ifndef SPIFLASHDISK_START
#  define SPIFLASHDISK_START    ((uint32_t)0)
#endif

//2 x 32KB flash pages (see reference manual / flash module organization)
# define FLASHDIVE_BLOCKS    SPIFLASHDISK_SIZE*1024/512  /*W25X40 max 512k*/

SpiEmbeddedFlashBlock block0(SPIFLASHDISK_START                             ,  (SPIFLASHDISK_SIZE/2) * 1024); 
SpiEmbeddedFlashBlock block1(SPIFLASHDISK_START +  (SPIFLASHDISK_SIZE/2) * 1024,  (SPIFLASHDISK_SIZE/2) * 1024);

// combine them into one virtual storage of 512 bytes
FlashVariables<512> SpiStorageBackend(&block0, &block1);

// SdFat interface, so we can access it from the microcontroller
FlashBlockFat fat(&SpiStorageBackend);

// USB interface so we can access it through USB
SpiBlockDevice SpiBlockDevice(FLASHDIVE_BLOCKS, &SpiStorageBackend);

// When we open the first time, and is not formatted, format it
void formatListener() {
  formatFat12(&SpiBlockDevice, FLASHDIVE_BLOCKS);
}

//Called by USB subsystem
BlockDevice *getMassStorage() {
  SpiBlockDevice.begin();
  SpiStorageBackend.setFormatListener(formatListener);
  //If the drive appears unformbeginatted, try this (should not be needed):
  //storageBackend.format();
  return &SpiBlockDevice;
}
