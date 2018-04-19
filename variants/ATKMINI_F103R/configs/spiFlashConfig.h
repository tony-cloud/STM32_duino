/* bsp_spiflash.h specific board spiflash config file, arduino have not autoload! */
#ifndef __SPIFLASHCONFIG_H__
#define __SPIFLASHCONFIG_H__

// W25Q64
#define SPIFLASH_DEV	SPI1
#define SPIFLASH_CS		PA2
#define SPIFLASH_SCK	PA5
#define SPIFLASH_MISO	PA6
#define SPIFLASH_MOSI	PA7
#define SPIFLASH_SPEED_Mhz 30

#endif   //__BSP_SPIFLASH_H__