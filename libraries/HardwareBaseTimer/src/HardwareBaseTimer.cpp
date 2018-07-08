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

  2018.5.28  fock from Daniel Fekete HardwareTimer lib and add basic timer TIM6/7 by huaweiwx
*/

#include "HardwareBaseTimer.h"

#include CHIP_PERIPHERAL_INCLUDE

#ifdef TIM6
  HardwareBaseTimer* interruptTimer6;
#endif

#ifdef TIM7
# if  FREERTOS == 0
  HardwareBaseTimer* interruptTimer7;
# endif
#endif

static void handleInterrupt(HardwareBaseTimer *timer);


void HardwareBaseTimer::resume(void) {
    bool hasInterrupt = false;
    if (callbacks[0] != NULL) {
       hasInterrupt = true;
    }

#ifdef TIM6
    if (handle.Instance == TIM6) {
        __HAL_RCC_TIM6_CLK_ENABLE();
        interruptTimer6 = this;
        if (hasInterrupt) {
#if defined(STM32F0)||defined(STM32F1)|| defined(STM32L0)||defined(STM32L1)||(STM32F412xx)
            HAL_NVIC_SetPriority(TIM6_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM6_IRQn);
#else
           HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
#endif
        }
    }
#endif

#ifdef TIM7
# if  FREERTOS == 0
    if (handle.Instance == TIM7) {
        __HAL_RCC_TIM7_CLK_ENABLE();
        interruptTimer7 = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM7_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM7_IRQn);
        }
    }
# endif
#endif

    handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

#if !defined(STM32L1) && !defined(STM32L0)  /*huaweiwx*/
    handle.Init.RepetitionCounter = 0;
#endif
    HAL_TIM_Base_Init(&handle);

    if (callbacks[0] != NULL) {
        HAL_TIM_Base_Start_IT(&handle);
    } else {

        HAL_TIM_Base_Start(&handle);
    }
}

uint32_t HardwareBaseTimer::getPrescaleFactor() {
    return handle.Init.Prescaler;
}

void HardwareBaseTimer::setPrescaleFactor(uint32_t prescaler) {
    handle.Init.Prescaler = prescaler;
}

uint32_t HardwareBaseTimer::getOverflow() {
    return handle.Init.Period;
}

void HardwareBaseTimer::setOverflow(uint32_t overflow) {
    handle.Init.Period = overflow;
}

uint32_t HardwareBaseTimer::getCount(void) {
    return __HAL_TIM_GET_COUNTER(&handle);
}

void HardwareBaseTimer::setCount(uint32_t counter) {
    __HAL_TIM_SET_COUNTER(&handle, counter);
}

#define MAX_RELOAD ((1 << 16) - 1) // Not always! 32 bit timers!

uint32_t HardwareBaseTimer::getBaseFrequency() {
#if defined(STM32F0)
    return HAL_RCC_GetPCLK1Freq();
#elif defined(STM32L0)||defined(STM32L1)
    return HAL_RCC_GetHCLKFreq();   /* hclk/timdiv(default 1) */
#elif defined(STM32F3)
    return HAL_RCC_GetPCLK2Freq();
#elif defined(STM32L4) // L/4
  #if defined(STM32L4R5xx)  
     return 2*HAL_RCC_GetPCLK1Freq();
  #else 
     return HAL_RCC_GetPCLK1Freq();  //L476
  #endif
#else  //F1/2/4/7
    return 2*HAL_RCC_GetPCLK1Freq();
#endif
}

uint32_t HardwareBaseTimer::setPeriod(uint32_t microseconds) {
    if (!microseconds) {
        this->setPrescaleFactor(1);
        this->setOverflow(1);
        return this->getOverflow();
    }

    uint32_t period_cyc = microseconds * (getBaseFrequency()  / 1000000); //TODO!

    uint32_t prescaler = (uint32_t)(period_cyc / MAX_RELOAD + 1);

    uint32_t overflow = (uint32_t)((period_cyc + (prescaler / 2)) / prescaler);

    this->setPrescaleFactor(prescaler);
    this->setOverflow(overflow);
    return overflow;
}



static void handleInterrupt(HardwareBaseTimer *timer) {
    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_UPDATE) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_UPDATE);
        if (timer->callbacks[0] != NULL) timer->callbacks[0]();
    }
}

#ifdef TIM6
 HardwareBaseTimer Timer6(TIM6);
#if defined(STM32F0)||defined(STM32F1)|| defined(STM32L0)||defined(STM32L1)||(STM32F412xx)
  extern "C" void TIM6_IRQHandler(void)
#else 
  extern "C" void TIM6_DAC_IRQHandler(void)
#endif
 {
    if (interruptTimer6 != NULL) handleInterrupt(interruptTimer6);
 }
#endif
#ifdef TIM7
# if FREERTOS == 0    
    HardwareBaseTimer Timer7(TIM7);
    
    extern "C" void TIM7_IRQHandler(void) {
       if (interruptTimer7 != NULL) handleInterrupt(interruptTimer7);
    }
# endif 
#endif

