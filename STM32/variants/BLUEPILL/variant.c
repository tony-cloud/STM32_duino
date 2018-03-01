#include "stm32_def.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"

void SystemClock_Config(void) __weak;
#if defined(USE_HSI)
void SystemClock_Config(void) {
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
 
    LL_RCC_HSI_Enable();
	
	while(LL_RCC_HSI_IsReady() != 1)
	{   
	}
    LL_RCC_HSI_SetCalibTrimming(16);
	
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);

    LL_RCC_PLL_Enable();

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);


    LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL);

    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

	LL_Init1msTick(48000000);
	
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);

    LL_SetSystemCoreClock(48000000);

    /* SysTick_IRQn interrupt configuration */
#if FREERTOS
  HAL_NVIC_SetPriority(PendSV_IRQn, SYSTICK_INT_PRIORITY, 0);
#endif
  HAL_NVIC_SetPriority(SysTick_IRQn, SYSTICK_INT_PRIORITY, 0);
  
  LL_SYSTICK_EnableIT();  //for LL enableIT huaweiwx@sina.com 2018.3.1
}

#else   //HSE
//HSE
void SystemClock_Config(void) {

    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	
    LL_RCC_HSE_Enable();

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

    LL_RCC_PLL_Enable();

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);


    LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);

    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

	LL_Init1msTick(72000000);
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SetSystemCoreClock(72000000);

    /* SysTick_IRQn interrupt configuration */
#if FREERTOS
  HAL_NVIC_SetPriority(PendSV_IRQn, SYSTICK_INT_PRIORITY, 0);
#endif
  HAL_NVIC_SetPriority(SysTick_IRQn, SYSTICK_INT_PRIORITY, 0);
  
  LL_SYSTICK_EnableIT();   //for LL enableIT huaweiwx@sina.com 2018.3.1
}

#endif
