#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

  #define  HAVE_SRAM
//#define  HAVE_24CXX     AT24C02
//#define  HAVE_SPIFLASH  W25Q64
  #define  HAVE_SDMMC     
  #define  HAVE_NAND
//#define  HAVE_NRF24L01   
//#define  HAVE_DS18B02   PB3
//#define  HAVE_IRREMOTE  PB4



#define  BEEP_PIN      PG7

/******************  BSP_TFT_LCD ******************/
#include "configs/LCDConfig.h"

#define LCD_ADDR_SETUPTIME 10       //FSMC time setup
#define LCD_DATA_SETUPTIME 25

//use NE4  A12(REG/DAT)
#define LCD_BASE_BK11       ((uint32_t)(0x60000000 | 0x00000000)) //PD1/NE1 FSMC_BANK1_1
#define LCD_BASE_BK12       ((uint32_t)(0x60000000 | 0x04000000)) //PG9/NE2 FSMC_BANK1_2
#define LCD_BASE_BK13       ((uint32_t)(0x60000000 | 0x08000000)) //PG10/NE3 FSMC_BANK1_3
#define LCD_BASE_BK14       ((uint32_t)(0x60000000 | 0x0C000000)) //PG12/NE4 FSMC_BANK1_4

#define TFT_LCD_BASE        ((uint32_t)(LCD_BASE_BK14 +(1 << 13)-2)) /*A12*/

#define  LCDBL_PIN	PF10

/******************  BSP_TFT_TOUCH ******************/
#define TOUCH_SPI  NONE
#define TOUCH_NCS  PB0
//#define TOUCH_BUSY PG8
#define TOUCH_SCK  PB114
#define TOUCH_MISO PB2
#define TOUCH_MOSI PB1
#define TOUCH_PEN  PF11

#define TOUCH_XOFF 38  //int16
#define TOUCH_XFAC 94.19  //float *1000
#define TOUCH_YOFF 29   //int16
#define TOUCH_YFAC 71.83 //float *1000
#define TOUCH_XYCHG 1

/******************  bsp_SRAM **********************/
#define SRAM_START            ((uint32_t)(0x60000000 | 0x08000000))
#define SRAM_LENGTH			  ((uint32_t)(1*1024*1024))



/******************  extern c functions **************/
#ifdef __cplusplus
extern "C"{
#endif

void STM_FSMC_LCD_Init(void);
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);
void STM_FSMC_SRAM_Init(void);
//void STM_FSMC_NAND_Init(void);

#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__