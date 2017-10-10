/* bsp.h arduino have not autoload! */
#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

/******************  BSP_TFT_LCD ******************/
#define BSP_TFT_LCD   SPFD5420
#define LCD_ADDR_SETUPTIME 10	/*FSMC time setup*/
#define LCD_DATA_SETUPTIME 25

//USE NE1 A18
#define LCD_BASE_BK11    ((uint32_t)(0x60000000 | 0x00000000)) /*PD1/NE1 FSMC_BANK1_1*/
#define TFT_LCD_BASE     ((uint32_t)(LCD_BASE_BK11 +(1 << 19)-2)) /*A18*/

#define  LCDBL_PIN   PC6

/******************  BSP_TFT_TOUCH ******************/
#define TOUCH_SPI  SPI1
#define TOUCH_NCS  PA8
#define TOUCH_BUSY PD3
#define TOUCH_SCK  PA5
#define TOUCH_MISO PA6
#define TOUCH_MOSI PA7
#define TOUCH_NIRQ PC7

#define TOUCH_XOFF 150
#define TOUCH_XFAC 86
#define TOUCH_YOFF 200 
#define TOUCH_YFAC 64 


#ifdef __cplusplus
extern "C"{
#endif

//void STM_FSMC_LCD_Init(void);
//void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);
#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__