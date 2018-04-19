/* spiflashconfig.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#define SPIFLASH_TYPE W25Q16
#define SPIFLASH_DEV	SPI1
#define SPIFLASH_CS	PB0
#define SPIFLASH_SCK	PB3
#define SPIFLASH_MISO	PB4
#define SPIFLASH_MOSI	PB5

#endif   //__BSP_SPIFLASH_H__