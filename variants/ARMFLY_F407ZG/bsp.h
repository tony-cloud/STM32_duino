#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

#define HAVE_SRAM
#define HAVE_NAND
//#define HAVE_NOR

#define HAVE_TOUCH
#define  HAVE_SDIO_SDMMC



/******************  BSP_FSMC DEVICE ******************/
//comman base address
#define LCD_BASE_BK11       ((uint32_t)(0x60000000 | 0x00000000)) //PD1/NE1 FSMC_BANK1_1
#define LCD_BASE_BK12       ((uint32_t)(0x60000000 | 0x04000000)) //PG9/NE2 FSMC_BANK1_2
#define LCD_BASE_BK13       ((uint32_t)(0x60000000 | 0x08000000)) //PG10/NE3 FSMC_BANK1_3
#define LCD_BASE_BK14       ((uint32_t)(0x60000000 | 0x0C000000)) //PG12/NE4 FSMC_BANK1_4

#include "configs/LCDConfig.h"
# define LCD_ADDR_SETUPTIME 20       //FSMC time setup
# define LCD_DATA_SETUPTIME 40
//BASE ADDR
# define TFT_LCD_BASE         LCD_BASE_BK14  /*use NE4 (REG/DAT)A0*/
//BACK LIGHT
# define  LCDBL_PIN   PB1


#ifdef HAVE_TOUCH
#define TOUCH_SPI  SPI1
#define TOUCH_NCS  PA4
#define TOUCH_BUSY PB5
#define TOUCH_SCK  PA5
#define TOUCH_MISO PA6
#define TOUCH_MOSI PA7
#define TOUCH_NIRQ PC5

#define TOUCH_XOFF 38  //int16
#define TOUCH_XFAC 94.19  //float *1000
#define TOUCH_YOFF 29   //int16
#define TOUCH_YFAC 71.83 //float *1000
#define TOUCH_XYCHG 1
#endif

// SRAM ISSI62WV51216 BANK1_3  
#ifdef HAVE_SRAM
#define SRAM_START            LCD_BASE_BK13
#define SRAM_LENGTH			  ((uint32_t)(1*1024*1024))  
#define SRAM_END              ((uint32_t)(SRAM_START+SRAM_LENGTH))
extern SRAM_HandleTypeDef sramHandle;
#endif

//have not norflash
#ifdef HAVE_NOR
#define NOR_DEVICE_ADDR      LCD_BASE_BK12
#define NOR_DEVICE_LENGTH    ((uint32_t)(2*1024*1024)) /* 39VF160 */
#endif


//nand HY27UF082G2M
#ifdef HAVE_NAND
#define NAND_PAGE_SIZE             ((uint16_t)0x0800) /* 2048 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16_t)0x0040) /* 64x2048 bytes pages per block */
#define NAND_PLANE_SIZE            ((uint16_t)0x0400) /* 2048 Block per plane */
#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040) /* last 64 bytes as spare area */
#define NAND_MAX_PLANE             ((uint16_t)0x0002) /* 2 zones of 2048 block */
extern NAND_HandleTypeDef nandHandle;
#endif

/******************  extern c functions **************/
#ifdef __cplusplus
extern "C"{
#endif

void STM_FSMC_LCD_Init(void);
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds);
void STM_FSMC_SRAM_Init(void);
void STM_FSMC_NAND_Init(void);

#ifdef __cplusplus
} //extern "C"
#endif

#endif   //__BSP_H__