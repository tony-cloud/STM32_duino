#include "stm32_build_defines.h"
#include "stm32_def.h"

#ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"


/** System Clock Configuration
*/
extern void Error_Handler(void);
#if defined(USE_HSI)
extern void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();
   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {   
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);
  LL_RCC_PLL_Enable();
   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }
  LL_Init1msTick(48000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(48000000);
  /* SysTick_IRQn interrupt configuration */
#if __has_include("FreeRTOS.h")  //huawei (huaweiwx@sina.com)
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);  
#else  
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif  
  LL_SYSTICK_EnableIT();  //for STM32F0 add systick enableIT huaweiwx@sina.com 2017.8.5
}

#else

# if   F_CPU == 96000000
#   define HSE_MUL LL_RCC_PLL_MUL_12
# elif F_CPU == 72000000
#   define HSE_MUL LL_RCC_PLL_MUL_9
# else  //F_CPU ==48000000
#   define HSE_MUL LL_RCC_PLL_MUL_6	
# endif
	
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  Error_Handler();  
  }
  LL_RCC_HSE_Enable();
   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, HSE_MUL);
  LL_RCC_PLL_Enable();
   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }
  LL_Init1msTick(F_CPU);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(F_CPU);
  /* SysTick_IRQn interrupt configuration */
#if __has_include("FreeRTOS.h")  //huawei (huaweiwx@sina.com)
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);  
#else  
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif  
  LL_SYSTICK_EnableIT();  //for STM32F0 add systick enableIT huaweiwx@sina.com 2017.8.5
}
#endif