/* Arduino SdFat BSP config file
 * huaweiwx@sina.com 2017.12.2 
 */
/**
 * \file
 * \brief configuration definitions
 */
#ifndef _SDCARDCONFIG_H_
#define _SDCARDCONFIG_H_

#define SDCARD_SPIX  SPI1
#define SDCARD_CS	 PA3
#define SDCARD_SCK	 PA5
#define SDCARD_MISO	 PA6
#define SDCARD_MOSI	 PA7

#define USE_STANDARD_SPI_LIBRARY 0
#define IMPLEMENT_SPI_PORT_SELECTION 1
#define USE_SDIO 0

#endif  // _SDCARDCONFIG_H_
