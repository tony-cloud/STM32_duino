/* spiflashconfig.h: The specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#define SPIFLASH_TYPE AT45DB161
#define SPIFLASH_DEV  SPI1
#define SPIFLASH_CS	PA4
#define SPIFLASH_SCK	PA5
#define SPIFLASH_MISO PA6
#define SPIFLASH_MOSI PA7

#endif   //__BSP_SPIFLASH_H__