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

#include "stm32_def.h"

extern void SystemClock_Config(void);

void init() {
#if defined(STM32F7)||defined(STM32H7)	
  SCB_EnableICache();  /* Enable I-Cache */
  SCB_EnableDCache();  /* Enable D-Cache */
#endif
  HAL_Init();
  SystemClock_Config();
}


#if FREERTOS == 0
void SysTick_Handler(void)	
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
#endif

void HAL_MspInit(void)
{
#ifdef STM32F1
  __HAL_RCC_AFIO_CLK_ENABLE();
#endif

#if (defined(STM32L0)||defined(STM32F0))
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVC_IRQn, CORTEX_INT_PRIORITY, 0);
#else	
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, CORTEX_INT_PRIORITY, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, CORTEX_INT_PRIORITY, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, CORTEX_INT_PRIORITY, 0);
  /* SVCall_IRQn interrupt configuration */
#if defined(STM32L1)  
  HAL_NVIC_SetPriority(SVC_IRQn, CORTEX_INT_PRIORITY, 0);
#else
  HAL_NVIC_SetPriority(SVCall_IRQn, CORTEX_INT_PRIORITY, 0);	
#endif	
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, CORTEX_INT_PRIORITY, 0);
#endif
  HAL_NVIC_SetPriority(PendSV_IRQn, SYSTICK_INT_PRIORITY, 0); /*move to here from variant.c huawei 2018.7.17*/
}


//void Error_Handler() {

//}
