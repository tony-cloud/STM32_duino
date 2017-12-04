/* bsp_spiflash.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

// W25Q64
#define SPIFLASH_DEV	SPI
#define SPIFLASH_CS		PB12
#define SPIFLASH_SCK	PB13
#define SPIFLASH_MISO	PB14
#define SPIFLASH_MOSI	PB15
#define SPIFLASH_SPEED_Mhz 80

#endif   //__BSP_SPIFLASH_H__