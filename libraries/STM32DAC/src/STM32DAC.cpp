#include "STM32DAC.h"
#include "stm32_dma.h"

#ifdef STM32H7
#define DAC DAC1
#define __HAL_RCC_DAC1_CLK_ENABLE __HAL_RCC_DAC12_CLK_ENABLE
#endif

static DAC_HandleTypeDef DAC_Handle[2];
static DAC_ChannelConfTypeDef  DAC_ChannelConf;

extern "C"
void DAC_Init(const uint32_t DACx, const uint32_t trig) {
	
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  if (DACx == DAC_CHANNEL_1) {
    GPIO_InitStruct.Pin = GPIO_PIN_4;
//    pinMode(PA4, INPUT);
  } 
#if defined(DAC_CHANNEL_2)
  else {
    GPIO_InitStruct.Pin = GPIO_PIN_5;
//    pinMode(PA5, INPUT);
  }
#endif

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#if defined(__HAL_RCC_DAC1_CLK_ENABLE)
  __HAL_RCC_DAC1_CLK_ENABLE();
#else
  __HAL_RCC_DAC_CLK_ENABLE();
#endif

  DAC_Handle[(uint8_t)DACx].Instance = DAC;
  HAL_DAC_Init(&DAC_Handle[(uint8_t)DACx]);
  
//  DAC_ChannelConf.DAC_SampleAndHold =  DAC_SAMPLEANDHOLD_DISABLE;
//  DAC_ChannelConf.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
//  DAC_ChannelConf.DAC_UserTrimming =  DAC_TRIMMING_FACTORY;

  DAC_ChannelConf.DAC_Trigger = trig;
  DAC_ChannelConf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

  
  if (DACx == DAC_CHANNEL_1) {
     HAL_DAC_ConfigChannel(&DAC_Handle[(uint8_t)DACx], &DAC_ChannelConf, DAC_CHANNEL_1);
     DAC->CR |= DAC_CR_EN1;
	 }
#if defined(DAC_CHANNEL_2)
  else {
    HAL_DAC_ConfigChannel(&DAC_Handle[(uint8_t)DACx], &DAC_ChannelConf, DAC_CHANNEL_2);
    DAC->CR |= DAC_CR_EN2;
  }
#endif  
}

extern "C"
void DAC_SetValue(uint32_t DACx, uint16_t value) {
  if (value > 0x0FFF) {
    value = 0x0FFF;
  }

  /* Set 12-bit value, right aligned */
  if (DACx == DAC_CHANNEL_1) {
    HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
  }
#if defined(DAC_CHANNEL_2)
  else {
    HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
  }
#endif  
}

extern "C"
uint16_t DAC_GetValue(uint32_t DACx) {
  if (DACx == DAC_CHANNEL_1) {
    return (uint16_t)HAL_DAC_GetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
  }
#if defined(DAC_CHANNEL_2)
  else{
    return (uint16_t)HAL_DAC_GetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
  }
#endif
}

extern "C"
void DACEx_TriangleWaveGenerate(uint32_t DACx, uint32_t Amplitude,uint32_t dataHolding){
  if (DACx == DAC_CHANNEL_1) {
    HAL_DACEx_TriangleWaveGenerate(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_1, Amplitude);
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
	HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1, DAC_ALIGN_12B_R, dataHolding);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DACEx_TriangleWaveGenerate(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_2, Amplitude);
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
	HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2, DAC_ALIGN_12B_R, dataHolding);
  }
#endif

}

extern "C"
void DACEx_NoiseWaveGenerate(uint32_t DACx, uint32_t Amplitude,uint32_t dataHolding){
  if (DACx == DAC_CHANNEL_1) {
    HAL_DACEx_NoiseWaveGenerate(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_1, Amplitude);
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
	HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1, DAC_ALIGN_12B_R, dataHolding);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DACEx_NoiseWaveGenerate(&DAC_Handle[(uint8_t)DACx], DAC_CHANNEL_2, Amplitude);
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
	HAL_DAC_SetValue(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2, DAC_ALIGN_12B_R, dataHolding);
  }
#endif
}

extern "C"
void DAC_Stop(uint32_t DACx) {
  if (DACx == DAC_CHANNEL_1) {
    HAL_DAC_Stop(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DAC_Stop(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
  }
#endif
}

extern "C"
void DAC_Start(uint32_t DACx) {
  if (DACx == DAC_CHANNEL_1) {
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DAC_Start(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
  }
#endif
}

static DMA_HandleTypeDef  hdma_dac1;  
extern "C"
void DAC_Start_DMA(uint32_t DACx, uint32_t* pData, uint32_t Length, uint32_t Alignment) {
    /* DMA1 clock enable */
#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7)
    __HAL_RCC_DMA1_CLK_ENABLE();
#else	
    __HAL_RCC_DMA2_CLK_ENABLE(); 
#endif
	
  stm32DmaAcquire(&hdma_dac1, DAC1_CH1, DAC, true);

//  hdma_dac1.Init.Request  = DMA_REQUEST_6;
  hdma_dac1.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_dac1.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_dac1.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_dac1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  hdma_dac1.Init.Mode                = DMA_NORMAL;
  hdma_dac1.Init.Priority            = DMA_PRIORITY_HIGH;

  HAL_DMA_Init(&hdma_dac1);
  
  __HAL_LINKDMA(&DAC_Handle[(uint8_t)DACx], DMA_Handle1, hdma_dac1);


  if (DACx == DAC_CHANNEL_1) {
    HAL_DAC_Start_DMA(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1, pData, Length, Alignment);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DAC_Start_DMA(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2, pData, Length, Alignment);
  }
#endif
}

extern "C"
void DAC_Stop_DMA(uint32_t DACx) {
  stm32DmaRelease(&hdma_dac1);
  if (DACx == DAC_CHANNEL_1) {
    HAL_DAC_Stop_DMA(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_1);
  }
#if defined(DAC_CHANNEL_2)
  else{
    HAL_DAC_Stop_DMA(&DAC_Handle[(uint8_t)DACx],DAC_CHANNEL_2);
  }
#endif
  /*##-3- Disable the DMA Stream ############################################*/
  /* De-Initialize the DMA Stream associate to DAC_Channel1 */
//  HAL_DMA_DeInit(&DAC_Handle[(uint8_t)DACx]->DMA_Handle1);
  /*##-4- Disable the NVIC for DMA ###########################################*/
//  HAL_NVIC_DisableIRQ(DMA1_Channel3_IRQn);
}

//extern "C"
//void DMA1_Channel3_IRQHandler(void)
//{
//    HAL_DMA_IRQHandler(&DAC_Handle[(uint8_t)0]->DMA_Handle1);
//}
