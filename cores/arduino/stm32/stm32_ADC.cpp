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

  2018 modify by huaweiwx@sina
*/

/**
   Implementation of Arduino methods:
   analogRead(): https://www.arduino.cc/en/Reference/AnalogRead

   TODO improve performance by saving if the pin was configured for analog, and do not configure again.
     also deconfigure from pinMode in this case
   TODO implement analogReadResolution
   TODO F1 has no resolution, map to arduino default 10 bits
   TODO check if ClockPrescaler can always be set to ADC_CLOCK_SYNC_PCLK_DIV4
*/
#include "Arduino.h"
#include "stm32_gpio_af.h"

#ifdef ADC_CLOCK_SYNC_PCLK_DIV6
#  define ADC_CLOCK_DIV ADC_CLOCK_SYNC_PCLK_DIV6
#elif defined(ADC_CLOCK_SYNC_PCLK_DIV4)
#  define ADC_CLOCK_DIV ADC_CLOCK_SYNC_PCLK_DIV4
#elif defined(ADC_CLOCK_SYNC_PCLK_DIV2)
#  define ADC_CLOCK_DIV ADC_CLOCK_SYNC_PCLK_DIV2
#elif defined(ADC_CLOCK_ASYNC_DIV1)
#  define ADC_CLOCK_DIV ADC_CLOCK_ASYNC_DIV1
#elif defined(ADC_CLOCKPRESCALER_PCLK_DIV2)
#  define ADC_CLOCK_DIV ADC_CLOCKPRESCALER_PCLK_DIV2
#elif defined(STM32F1)
#  define ADC_CLOCK_DIV
#else
#  error "Unknown clock"
#endif

#ifdef STM32H7
#define __HAL_RCC_ADC2_CLK_ENABLE __HAL_RCC_ADC12_CLK_DISABLE
#elif defined(STM32F3)
#define __HAL_RCC_ADC3_CLK_ENABLE __HAL_RCC_ADC34_CLK_ENABLE
#define __HAL_RCC_ADC4_CLK_ENABLE __HAL_RCC_ADC34_CLK_ENABLE
#endif

#ifndef __HAL_RCC_ADC2_CLK_ENABLE
#define __HAL_RCC_ADC2_CLK_ENABLE __HAL_RCC_ADC_CLK_ENABLE
#endif

#ifndef __HAL_RCC_ADC3_CLK_ENABLE
#define __HAL_RCC_ADC3_CLK_ENABLE __HAL_RCC_ADC_CLK_ENABLE
#endif

static int readResolution = 10;
#ifdef ADC4
static ADC_HandleTypeDef handle[4];
#elif defined(ADC3)
static ADC_HandleTypeDef handle[3];
#elif defined(ADC2)
static ADC_HandleTypeDef handle[2];
#else
static ADC_HandleTypeDef handle[1];
#endif

extern "C"
void analogReadResolution(int resolution) {
  readResolution = resolution;
}

extern "C"
int analogReadResolutionVal(void) {
  return  readResolution;
}

extern "C"
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
#ifdef __HAL_RCC_ADC_FORCE_RESET
  __HAL_RCC_ADC_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC_RELEASE_RESET
  __HAL_RCC_ADC_RELEASE_RESET();
#endif

  if (hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_FORCE_RESET
    __HAL_RCC_ADC1_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_RELEASE_RESET
    __HAL_RCC_ADC1_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_CLK_DISABLE
    __HAL_RCC_ADC1_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_DISABLE
    __HAL_RCC_ADC12_CLK_DISABLE();
#endif
  }
#ifdef ADC2
  else if (hadc->Instance == ADC2) {
#ifdef __HAL_RCC_ADC2_FORCE_RESET
    __HAL_RCC_ADC2_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_RELEASE_RESET
    __HAL_RCC_ADC2_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC3
  else if (hadc->Instance == ADC3) {
#ifdef __HAL_RCC_ADC3_FORCE_RESET
    __HAL_RCC_ADC3_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_RELEASE_RESET
    __HAL_RCC_ADC3_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_FORCE_RESET
    __HAL_RCC_ADC34_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC3_CLK_DISABLE
    __HAL_RCC_ADC3_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
#endif
  }
#endif
#ifdef ADC4
  else if (hadc->Instance == ADC4) {
    __HAL_RCC_ADC34_FORCE_RESET();
    __HAL_RCC_ADC34_RELEASE_RESET();
    __HAL_RCC_ADC34_CLK_DISABLE();
  }
#endif
#ifdef __HAL_RCC_ADC_CLK_DISABLE
  __HAL_RCC_ADC_CLK_DISABLE();
#endif
}


#ifdef ADC_OFFSET_NONE  //F3/H7/L4
extern "C"
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode)
#else
extern "C"
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch)
#endif
{
  int instanceIndex = 0;
#ifdef ADC2
  if (ADCx == ADC2) {
    instanceIndex = 1;
    __HAL_RCC_ADC2_CLK_ENABLE();
  }
#endif
#ifdef ADC3
  if (ADCx == ADC3) {
    instanceIndex = 2;
    __HAL_RCC_ADC3_CLK_ENABLE();
  }
#endif
#ifdef ADC4
  if (ADCx == ADC4) {
    instanceIndex = 3;
    __HAL_RCC_ADC4_CLK_ENABLE();
  }
#endif

  if (instanceIndex == 0) {
#ifdef __HAL_RCC_ADC1_CLK_ENABLE   //L4 only undef  huaweiwx@sina.com 2017.12
    __HAL_RCC_ADC1_CLK_ENABLE();
#elif defined(__HAL_RCC_ADC12_CLK_ENABLE) //H4 
    __HAL_RCC_ADC12_CLK_ENABLE();
#else  // __HAL_RCC_ADC_CLK_ENABLE  //L4 only 
    __HAL_RCC_ADC_CLK_ENABLE();
#endif
  }

  handle[instanceIndex].Instance = ADCx;


#ifdef STM32F1
  handle[instanceIndex].Init.ExternalTrigConv = ADC_SOFTWARE_START;
#else
  handle[instanceIndex].Init.ExternalTrigConv = ADC_SOFTWARE_START;
  handle[instanceIndex].Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;

  handle[instanceIndex].Init.ClockPrescaler = ADC_CLOCK_DIV;

#  ifndef STM32H7
  handle[instanceIndex].Init.DMAContinuousRequests = DISABLE;
#  endif

#  if MAX_RESOLUTION > 12
  handle[instanceIndex].Init.Resolution = ADC_RESOLUTION_16B;
#  else
  handle[instanceIndex].Init.Resolution = ADC_RESOLUTION_12B;
#  endif

#endif

  handle[instanceIndex].Init.ScanConvMode = DISABLE;
  handle[instanceIndex].Init.ContinuousConvMode = DISABLE;
  handle[instanceIndex].Init.DiscontinuousConvMode = DISABLE;

#if defined(STM32H7)
  handle[instanceIndex].Init.Overrun = ADC_OVR_DATA_PRESERVED;
  handle[instanceIndex].Init.LowPowerAutoWait = DISABLE;
  handle[instanceIndex].Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
//  handle[instanceIndex].Init.BoostMode = DISABLE;
  handle[instanceIndex].Init.OversamplingMode = DISABLE;
#else
  handle[instanceIndex].Init.DataAlign = ADC_DATAALIGN_RIGHT;
#endif

#if !defined(STM32L0) && !defined(STM32F0)
  handle[instanceIndex].Init.NbrOfConversion       = 1;
  handle[instanceIndex].Init.NbrOfDiscConversion   = 0;
# ifdef STM32F3
  handle[instanceIndex].Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
# endif

#else
  handle[instanceIndex].Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
  handle[instanceIndex].Init.LowPowerAutoPowerOff  = DISABLE;                       /* ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered */
  handle[instanceIndex].Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;

# ifdef STM32L0
  handle[instanceIndex].Init.SamplingTime       = ADC_SAMPLETIME_12CYCLES_5;
# else //STM32F0
  handle[instanceIndex].Init.SamplingTimeCommon = ADC_SAMPLETIME_13CYCLES_5;
# endif

#endif

#ifdef ADC_EOC_SINGLE_CONV
  handle[instanceIndex].Init.EOCSelection = ADC_EOC_SINGLE_CONV;
#endif

  HAL_StatusTypeDef error = HAL_ADC_Init(&handle[instanceIndex]);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_Init failed, error: %d", error);
    return 0;
  }

  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ch;

#ifdef ADC_RANK_CHANNEL_NUMBER
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
#else
  sConfig.Rank = 1;
#endif

#ifdef ADC_OFFSET_NONE  //F3/H7/L4
  sConfig.SingleDiff   = differentialMode;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
#endif


#ifdef STM32L0
#elif defined(STM32F4)
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfig.Rank = 1;
  sConfig.Offset = 0;
  //in handle
#elif defined(STM32H7)
  sConfig.Rank         = ADC_REGULAR_RANK_1;         /* Rank of sampled channel number ADCx_CHANNEL */
  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.OffsetRightShift       = DISABLE;                    /* No Right Offset Shift */
  sConfig.OffsetSignedSaturation = DISABLE;                    /* No Signed Saturation */
#elif defined(ADC_SAMPLETIME_19CYCLES_5)
  sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
#elif defined(ADC_SAMPLETIME_16CYCLES)
  sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES;
#elif defined(ADC_SAMPLETIME_15CYCLES)
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
#elif defined(ADC_SAMPLETIME_13CYCLES_5)
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
#elif defined(ADC_SAMPLETIME_12CYCLES_5)
  sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
#else
#error "unknown sampleing time"
#endif

  error = HAL_ADC_ConfigChannel(&handle[instanceIndex], &sConfig);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_ConfigChannel failed, error: %d", error);
    return 0;
  }

  error = HAL_ADC_Start(&handle[instanceIndex]);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_Start failed, error: %d", error);
    return 0;
  }

  error = HAL_ADC_PollForConversion(&handle[instanceIndex], 1000);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_PollForConversion failed, error: %d", error);
    return 0;
  }

  volatile int ret = HAL_ADC_GetValue(&handle[instanceIndex]);

  HAL_ADC_Stop(&handle[instanceIndex]);

  HAL_ADC_DeInit(&handle[instanceIndex]);

  return ret;
}

#ifdef ADC_OFFSET_NONE  //F3/H7/L4
extern "C"
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode, uint8_t n)
{
  int rtn = analogReadChanel(ADCx, ch, differentialMode);
  rtn = 0;
  for (auto i = 0; i < n; i++) {
    rtn += analogReadChanel(ADCx, ch, differentialMode);
  }
  return rtn / n;
}
#else
extern "C"
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch, uint8_t n)
{
  int rtn = analogReadChanel(ADCx, ch);
  rtn = 0;
  for (uint8_t i = 0; i < n; i++) {
    rtn += analogReadChanel(ADCx, ch);
  }
  return rtn / n;
}
#endif

extern "C"
int analogRead(uint8_t pin) {
#ifdef A0
  if (pin == 0) pin = A0;
#endif
#ifdef A1
  if (pin == 1) pin = A1;
#endif
#ifdef A2
  if (pin == 2) pin = A2;
#endif
#ifdef A3
  if (pin == 3) pin = A3;
#endif
#ifdef A4
  if (pin == 4) pin = A4;
#endif
#ifdef A5
  if (pin == 5) pin = A5;
#endif
#ifdef A6
  if (pin == 6) pin = A6;
#endif

  stm32_chip_adc1_channel_type config = stm32ADC1GetChannel(variant_pin_list[pin].port, variant_pin_list[pin].pinMask, 0);

  if (config.instance == NULL) {
    return 0;
  }

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = variant_pin_list[pin].pinMask;
#ifdef GPIO_MODE_ANALOG_ADC_CONTROL  /*STM32L4*/
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
#else
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
#endif
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(variant_pin_list[pin].port, &GPIO_InitStruct);
#ifdef  ADC_OFFSET_NONE
  return analogReadChanel(config.instance, config.channel, ADC_SINGLE_ENDED) >> (MAX_RESOLUTION - readResolution);
#else
  return analogReadChanel(config.instance, config.channel) >> (MAX_RESOLUTION - readResolution);
#endif
}

#if 0 //def ADC_CHANNEL_VBAT
extern "C"
void ADC_EnableVbat(void) {
	/* Enable VBAT */
#if defined(ADC_CCR_VBATEN)
	ADC->CCR |= ADC_CCR_VBATEN;
#else
	ADC->CCR |= ADC_CCR_VBATE;
#endif
}

extern "C"
void ADC_DisableVbat(void) {
	/* Disable VBAT */
#if defined(ADC_CCR_VBATEN)
	ADC->CCR &= ~ADC_CCR_VBATEN;
#else
	ADC->CCR &= ~ADC_CCR_VBATE;
#endif
}
#endif


ADCClass adc;
