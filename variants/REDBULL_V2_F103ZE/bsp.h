#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

//device status
#define  HAVE_SRAM
#define  HAVE_NAND
#define  HAVE_NOR

#define  HAVE_TFT_LCD
#define  HAVE_TOUCH
#define  HAVE_SPIFLASH
#define  HAVE_24CXX

 
#define  BEEP_PIN             PB10

/******************  BSP_FSMC DEVICE ******************/
//comman base address
#define LCD_BASE_BK11	((uint32_t)(0x60000000 | 0x00000000)) //PD1/NE1 FSMC_BANK1_1
#define LCD_BASE_BK12	((uint32_t)(0x60000000 | 0x04000000)) //PG9/NE2 FSMC_BANK1_2
#define LCD_BASE_BK13	((uint32_t)(0x60000000 | 0x08000000)) //PG10/NE3 FSMC_BANK1_3
#define LCD_BASE_BK14	((uint32_t)(0x60000000 | 0x0C000000)) //PG12/NE4 FSMC_BANK1_4

#include "configs/LCDConfig.h"
#define LCD_ADDR_SETUPTIME 30       //FSMC addr time setup
#define LCD_DATA_SETUPTIME 45       //FSMC data time setup
#define TFT_LCD_BASE          LCD_BASE_BK14        //use NE4 A0
#define LCDBL_PIN   PA1

#ifdef HAVE_TOUCH
#define TOUCH_SPI  SPI2
#define TOUCH_NCS  PB12
#define TOUCH_SCK  PB13
#define TOUCH_MISO PB14
#define TOUCH_MOSI PB15
#define TOUCH_NIRQ PG7
#define TOUCH_BUSY PG8

#define TOUCH_XOFF 38  //int16
#define TOUCH_XFAC 94.19  //float *1000
#define TOUCH_YOFF 29   //int16
#define TOUCH_YFAC 71.83 //float *1000
#define TOUCH_XYCHG 1
#endif

#define TFT_SD_CS  PG15

// SRAM BANK1_3
#ifdef HAVE_SRAM
#define SRAM_START	LCD_BASE_BK13
#define SRAM_LENGTH	((uint32_t)(1*512*1024))
#endif

//nor
#ifdef HAVE_NOR
#define NOR_DEVICE_ADDR	LCD_BASE_BK12
#define NOR_DEVICE_LENGTH    ((uint32_t)(2*1024*1024)) /* 39VF160 */
#define NOR_WAIT_PIN    PD6
#endif

//nand
#ifdef HAVE_NAND
#define NAND_PAGE_SIZE             ((uint16_t)0x0200) /* 512 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16_t)0x0020) /* 32x512 bytes pages per block */
#define NAND_PLANE_SIZE            ((uint16_t)0x0400) /* 1024 Block per plane */
#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0010) /* last 16 bytes as spare area */
#define NAND_MAX_PLANE             ((uint16_t)0x1000) /* 4 planes of 1024 block */
#endif

#ifdef __cplusplus
extern "C"{
#endif

void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);
void STM_FSMC_LCD_Init(void);
void STM_FSMC_SRAM_Init(void);
uint8_t STM_FSMC_NOR_Init(void);
void STM_FSMC_NAND_Init(void);

#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__