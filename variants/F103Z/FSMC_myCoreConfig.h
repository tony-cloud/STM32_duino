#ifndef __FSMCMYCORECONFIG_H__
#define __FSMCMYCORECONFIG_H__

//my 103zet6 core

//sram CY62157EV30L
#define FSMC_SRAMBANK   FSMC_NORSRAM_BANK2
#define SRAM_LENGTH	    ((uint32_t)(1*1024*1024))  /* 51216 1M byte length*/
//#define FSMC_ADDRESSBITS 19                  /* 512K*16 19bit */

//nor MX29LV640
#define FSMC_NORBANK          FSMC_NORSRAM_BANK3
#define NOR_DEVICE_LENGTH     ((uint32_t)(8*1024*1024)) /* 4M*16bit 8M byte length*/
#define NOR_WAIT_PIN          PD6
#define FSMC_ADDRESSBITS      22                    /* 4M*16 22bit */

//nand K9F1G08U0B
#define FSMC_NANDBANK  FSMC_NAND_BANK2
#define FSMC_NWAIT_PD6  1
#define FSMC_INT2  1


#define NAND_PAGE_SIZE             ((uint16_t)0x0200) /* 512 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16_t)0x0020) /* 32x512 bytes pages per block */
#define NAND_PLANE_SIZE            ((uint16_t)0x0400) /* 1024 Block per plane */
#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0010) /* last 16 bytes as spare area */
#define NAND_MAX_PLANE             ((uint16_t)0x1000) /* 4 planes of 1024 block */

//lcd
//#define FSMC_LCDBANK  FSMC_NAND_BANK4

#define NORSRAM_BANKS  (NORSRAM_BANK1_1|NORSRAM_BANK1_2|NORSRAM_BANK1_3 /*|NORSRAM_BANK1_4*/) 

#define NORSRAM_BANK1_1  0x01
#define NORSRAM_BANK1_2  0x02
#define NORSRAM_BANK1_3  0x04
#define NORSRAM_BANK1_4  0x08

#define FSMC_BASE_BK11	(0x60000000 | 0x00000000) //PD7/NE1 FSMC_BANK1_1
#define FSMC_BASE_BK12	(0x60000000 | 0x04000000) //PG9/NE2 FSMC_BANK1_2
#define FSMC_BASE_BK13	(0x60000000 | 0x08000000) //PG10/NE3 FSMC_BANK1_3
#define FSMC_BASE_BK14	(0x60000000 | 0x0C000000) //PG12/NE4 FSMC_BANK1_4

//sram
#if FSMC_SRAMBANK == FSMC_NORSRAM_BANK1
#define SRAM_START	FSMC_BASE_BK11
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK2
#define SRAM_START	FSMC_BASE_BK12
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK3
#define SRAM_START	FSMC_BASE_BK13
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK4
#define SRAM_START	FSMC_BASE_BK14
#endif

//nor
#if FSMC_NORBANK == FSMC_NORSRAM_BANK1
#define NOR_DEVICE_ADDR	FSMC_BASE_BK11
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK2
#define NOR_DEVICE_ADDR	FSMC_BASE_BK12
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK3
#define NOR_DEVICE_ADDR	FSMC_BASE_BK13
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK4
#define NOR_DEVICE_ADDR	FSMC_BASE_BK14
#endif


#ifdef __cplusplus
extern "C"{
#endif

void    STM_FSMC_SRAM_Init(void);
uint8_t STM_FSMC_NOR_Init(void);
void    STM_FSMC_NAND_Init(void);

#ifdef __cplusplus
} //extern "C"
#endif

#if USE_EXTRAMSYSMALLOC
void setHeapAtSram(void);
#endif

#endif /* __FSMCMYCORECONFIG_H__ */
