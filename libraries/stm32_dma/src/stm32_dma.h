/*
  Copyright (c) 2017 Daniel Fekete

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef __STM32_DMA_H__
#define __STM32_DMA_H__

#include "stdbool.h"

typedef enum {
  SPI_TX,
  SPI_RX,
  SDIO_RXTX,
  DAC1_CH1,
  DAC1_CH2,
} dmaRequest;


#ifdef __cplusplus
extern "C" {
#endif

bool stm32DmaAcquire(DMA_HandleTypeDef *handle, dmaRequest request, void *periphInstance,  bool enableIrq);
void stm32DmaRelease(DMA_HandleTypeDef *handle);

#ifdef __cplusplus
}

template<const uint8_t request = 0>
class STM32DMA
{
  public:
  enum DMA_Request:uint8_t
  {
	SPI_TX,
	SPI_RX,
	SDIO_RXTX,
	DAC1_CH1,
	DAC1_CH2,
	MEMTOMEM,
	ADC1_DR,
	ADC2_DR,
	ADC3_DR,
  };

    DMA_HandleTypeDef hdma_handle;
    STM32DMA() {}

    HAL_StatusTypeDef Init(DMA_HandleTypeDef *handle, void *periphInstance,  bool enableIrq) {
      switch (request) {
        case SPI_TX:
        case SPI_RX:
        case SDIO_RXTX:
        case DAC1_CH1:
        case DAC1_CH2:
          if (stm32DmaAcquire(handle, request, periphInstance, enableIrq)) return HAL_OK;
          break;
        default:
          break;
      }
      return HAL_ERROR;
    }



#if defined(STM32F0) || defined(STM32F1) || defined(STM32F3) || defined(STM32L0)|| defined(STM32L1)||defined(STM32L4)
    HAL_StatusTypeDef Init(DMA_Channel_TypeDef* channel = DMA1_Channel7)
#elif defined(STM32F2) || defined(STM32F4) || defined(STM32F7)
    HAL_StatusTypeDef Init(DMA_Stream_TypeDef* channel = DMA2_Stream7)
#elif defined(STM32H7)
    HAL_StatusTypeDef Init(DMAMUX_Channel_TypeDef* channel = DMAMUX2_Channel7)
#endif
    {
	  __HAL_RCC_DMA1_CLK_ENABLE();
#ifdef __HAL_RCC_DMA2_CLK_ENABLE
	  __HAL_RCC_DMA2_CLK_ENABLE();
#endif

	  switch (request) {
        case MEMTOMEM:
          /* Configure DMA request channel */
#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7)
          /* Configure DMA request hdma_handle_dma2_stream7 on channel */
          hdma_handle.Init.Channel = DMA_CHANNEL_0;
          hdma_handle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
          hdma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
          hdma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
          hdma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
#endif
          hdma_handle.Instance = channel;
          hdma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
          hdma_handle.Init.Direction = DMA_MEMORY_TO_MEMORY;
          hdma_handle.Init.PeriphInc = DMA_PINC_ENABLE;
          hdma_handle.Init.MemInc = DMA_MINC_ENABLE;
          hdma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
          hdma_handle.Init.Mode = DMA_NORMAL;
          hdma_handle.Init.Priority = DMA_PRIORITY_LOW;
          return HAL_DMA_Init(&hdma_handle);
          break;
        case ADC1_DR:
        case ADC2_DR:
        case ADC3_DR:
          break;
        default:
          break;
      }
      return HAL_ERROR;
    }

    HAL_StatusTypeDef start(uint32_t *SrcAddress, uint32_t  *DstAddress, uint32_t DataLength) {
      if (request == MEMTOMEM)
        return  HAL_DMA_Start(&hdma_handle, (uint32_t)SrcAddress, (uint32_t)DstAddress, DataLength);
      else
        return HAL_ERROR;
    }

    HAL_StatusTypeDef start(uint32_t *SrcAddress, uint32_t  *DstAddress, unsigned int DataLength)
    {
      return  start(SrcAddress, DstAddress, (uint32_t)DataLength);
    }

};
#endif //__cplusplus

#endif //__STM32_DMA_H__
