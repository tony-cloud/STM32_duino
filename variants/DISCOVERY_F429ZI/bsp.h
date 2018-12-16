/**
  ******************************************************************************
  * @file    stm32f429i_discovery_sdram.h
  * @author  MCD Application Team
  * @version V2.1.4
  * @date    06-May-2016
  * @brief   This file contains all the functions prototypes for the 
  *          stm32f429i_discovery_sdram.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */   

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H__
#define __BSP_H__

#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "stm32f429i_discovery.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
 
/** @addtogroup STM32F429I_DISCOVERY_SDRAM
  * @{
  */
  
/** @defgroup STM32F429I_DISCOVERY_SDRAM_Exported_Types STM32F429I DISCOVERY SDRAM Exported Types
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_SDRAM_Exported_Constants STM32F429I DISCOVERY SDRAM Exported Constants
  * @{
  */ 
/**
  * @brief  FMC SDRAM Bank address
  */   
#define SDRAM_DEVICE_ADDR         0xD0000000U
#define SDRAM_DEVICE_SIZE         0x800000U    /* SDRAM device size in MBytes */
  
#define SDRAM_START               SDRAM_DEVICE_ADDR
#define SDRAM_LENGTH              SDRAM_DEVICE_SIZE
/**
  * @}
  */
  
/** @defgroup STM32F429I_DISCOVERY_SDRAM_Exported_Macro STM32F429I DISCOVERY SDRAM Exported Macro
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_SDRAM_Exported_Functions STM32F429I DISCOVERY SDRAM Exported Functions
  * @{
  */
void              BSP_SDRAM_Init(void);
void              BSP_SDRAM_Initialization_sequence(uint32_t RefreshCount);
void              BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize);
void              BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize);
void              BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize);
void              BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t* pData, uint32_t uwDataSize);
HAL_StatusTypeDef BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);
void              BSP_SDRAM_DMA_IRQHandler(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */   

/**
  * @}
  */

#if USE_EXTRAMSYSMALLOC
void setHeapAtSram(void);
void setHeapAtCCram(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_SDRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
