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
#define SDCARD_CS	 PD2
#define SDCARD_SCK	 PB13
#define SDCARD_MISO	 PB14
#define SDCARD_MOSI	 PB15


#define USE_SDIO 1

#endif  // _SDCARDCONFIG_H_
