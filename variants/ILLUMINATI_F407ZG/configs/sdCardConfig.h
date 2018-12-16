/* Arduino SdFat BSP config file
 * huaweiwx@sina.com 2017.12.2 
 */
/**
 * \file
 * \brief configuration definitions
 */
#ifndef _SDCARDCONFIG_H_
#define _SDCARDCONFIG_H_

/* test soft spi use only */
                   /*PC9     3 DAT1 */
#define SDCARD_MISO	 PC8   /*4 DAT0 */
#define SDCARD_SCK	 PC12  /*6 CLK  */
#define SDCARD_MOSI	 PD2   /*8 CMD  */  
#define SDCARD_CS	 PC11  /*9 CD/DAT3 */
                  /* PC10    10 DAT2   */ 

#endif  // _SDCARDCONFIG_H_
