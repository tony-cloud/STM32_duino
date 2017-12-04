/* bsp.h arduino have not autoload! */
#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

/******************  BSP_TFT_LCD ******************/
#include "configs/LCDConfig.h"
#define LCD_ADDR_SETUPTIME 30	/*FSMC time setup*/
#define LCD_DATA_SETUPTIME 50

//USE NE1 A18
#define LCD_BASE_BK11    ((uint32_t)(0x60000000 | 0x00000000)) /*PD1/NE1 FSMC_BANK1_1*/
#define TFT_LCD_BASE     ((uint32_t)(LCD_BASE_BK11 +(1 << 19)-2)) /*LCD_RS A18*/

#define  LCDBL_PIN   PC6

/******************  BSP_TFT_TOUCH ******************/
#define TOUCH_SPI  SPI1
#define TOUCH_NCS  PA8
#define TOUCH_NIRQ PC7
#define TOUCH_BUSY PD3
#define TOUCH_SCK  PA5
#define TOUCH_MISO PA6
#define TOUCH_MOSI PA7

#define TOUCH_XOFF 38  //int16
#define TOUCH_XFAC 94.19  //float *1000
#define TOUCH_YOFF 29   //int16
#define TOUCH_YFAC 71.83 //float *1000
#define TOUCH_XYCHG 1

/****************** other ****************************/
#define DS18B20_DQ_PIN  PB3
#define IRREMOTE_PIN  PB4

#ifdef __cplusplus
extern "C"{
#endif

void STM_FSMC_LCD_Init(void);
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);
#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__