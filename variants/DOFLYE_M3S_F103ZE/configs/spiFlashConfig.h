/* spiflashconfig.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#define SPIFLASH_TYPE W25Q64
#define SPIFLASH_DEV	SPI1
#define SPIFLASH_CS		PB12
#define SPIFLASH_SCK	PB13
#define SPIFLASH_MISO	PB14
#define SPIFLASH_MOSI	PB15

#endif   //__BSP_SPIFLASH_H__