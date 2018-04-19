#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

/******************  BSP_TFT_LCD ******************/
#include "configs/LCDConfig.h"
#define LCD_ADDR_SETUPTIME 20       //FSMC time setup
#define LCD_DATA_SETUPTIME 40

//USE NE1 A18
#define LCD_BASE_BK11       ((uint32_t)(0x60000000 | 0x00000000)) //PD1/NE1 FSMC_BANK1_1
//#define LCD_BASE_BK12     ((uint32_t)(0x60000000 | 0x04000000)) //PG9/NE2 FSMC_BANK1_2
//#define LCD_BASE_BK13     ((uint32_t)(0x60000000 | 0x08000000)) //PG10/NE3 FSMC_BANK1_3
//#define LCD_BASE_BK14     ((uint32_t)(0x60000000 | 0x0C000000)) //PG12/NE4 FSMC_BANK1_4
#define TFT_LCD_BASE     ((uint32_t)(LCD_BASE_BK11 +(1 << 19)-2))  //A18

#define  LCDBL_PIN   PB1

/******************  BSP_TFT_TOUCH ******************/
#define TOUCH_SPI  SPI2
#define TOUCH_NCS  PB12
//#define TOUCH_BUSY PB5
#define TOUCH_SCK  PB13
#define TOUCH_MISO PB14
#define TOUCH_MOSI PB15
#define TOUCH_NIRQ PC5

#define TOUCH_XOFF 38  //int16
#define TOUCH_XFAC 94.19  //float *1000
#define TOUCH_YOFF 29   //int16
#define TOUCH_YFAC 71.83 //float *1000
#define TOUCH_XYCHG 1

#ifdef __cplusplus
extern "C" {
#endif

void STM_FSMC_LCD_Init(void);
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);

#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__