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

  2018.5.18  add TIM5/8~22 by huaweiwx
  2018.5.28  for F3/F7/L4/H7 support channel5&6 by huaweiwx
*/

#include "HardwareTimer.h"

#include CHIP_PERIPHERAL_INCLUDE

HardwareTimer *interruptTimers[18];

extern void (*pwm_callback_func)();
static void handleInterrupt(HardwareTimer *timer);

static const uint32_t OCMODE_NOT_USED = 0xFFFF;

HardwareTimer::HardwareTimer(TIM_TypeDef *instance, const stm32_tim_pin_list_type *pin_list, int pin_list_size) {
    this->tim_pin_list = pin_list;
    this->tim_pin_list_size = pin_list_size;

    handle.Instance = instance;

    for(int i=0; i < TIMER_CHANNELS; i++) {
        channelOC[i].OCMode = OCMODE_NOT_USED;
        channelOC[i].OCPolarity = TIM_OCPOLARITY_HIGH;
        channelOC[i].OCFastMode = TIM_OCFAST_DISABLE;
		
#if  !defined(STM32L0)
        channelOC[i].OCIdleState = TIM_OCIDLESTATE_RESET;
#endif

#if !defined(STM32L1) && !defined(STM32L0)
        channelOC[i].OCNPolarity = TIM_OCNPOLARITY_HIGH;
        channelOC[i].OCNIdleState = TIM_OCNIDLESTATE_RESET;
#endif
        channelIC[i].ICPolarity = OCMODE_NOT_USED;
        channelIC[i].ICSelection = TIM_ICSELECTION_DIRECTTI;
        channelIC[i].ICPrescaler = TIM_ICPSC_DIV1;
        channelIC[i].ICFilter = 0;
    }
}

void HardwareTimer::pause() {
    HAL_TIM_Base_Stop(&handle);
}

void HardwareTimer::resume(int channel, TIMER_MODES mode) {
    bool hasInterrupt = false;
    for(size_t i=0; i<sizeof(callbacks) / sizeof(callbacks[0]); i++) {
        if (callbacks[i] != NULL) {
            hasInterrupt = true;
            break;
        }
    }

#ifdef TIM1 
    if (handle.Instance == TIM1) {
        __HAL_RCC_TIM1_CLK_ENABLE();
        interruptTimers[0] = this;
        if (hasInterrupt) {
#if (STM32F410Cx || STM32F410Rx || STM32F410Tx)  /*F4 TIM1_UP_TIM10_IRQn. but F410 exception*/
            HAL_NVIC_SetPriority(TIM1_UP_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);	
#elif defined(STM32F3)||defined(STM32L4)|| STM32F100xB|| STM32F100xE /*F100 TIM1_UP_TIM16*/
            HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
#elif defined(STM32F1)||defined(STM32F2)||defined(STM32F4)|| defined(STM32F7)||defined(STM32H7)
            HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
#endif
            HAL_NVIC_SetPriority(TIM1_CC_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
        }

        TIM_ClockConfigTypeDef sClockSourceConfig;
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        HAL_TIM_ConfigClockSource(&handle, &sClockSourceConfig);

        TIM_MasterConfigTypeDef sMasterConfig;
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        HAL_TIMEx_MasterConfigSynchronization(&handle, &sMasterConfig);

        handle.Init.RepetitionCounter = 0;
    }
#endif

#ifdef TIM2
    if (handle.Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
		
#ifndef TIM3		
        pwm_callback_func = []() { handleInterrupt(interruptTimers[1]); };
#endif		
        interruptTimers[1] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM2_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM2_IRQn);
        }
    }
#endif

#ifdef TIM3
    if (handle.Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_ENABLE();
        pwm_callback_func = []() { handleInterrupt(interruptTimers[2]); };
        interruptTimers[2] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM3_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM3_IRQn);
        }
    }
#endif

#ifdef TIM4
    if (handle.Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_ENABLE();
        interruptTimers[3] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM4_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM4_IRQn);
        }
    }
#endif

//add by huaweiwx@sina.com 2018.5.28
#ifdef TIM5
    if (handle.Instance == TIM5) {
        __HAL_RCC_TIM5_CLK_ENABLE();
        interruptTimers[4] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM5_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM5_IRQn);
        }
    }
#endif

#ifdef TIM8
    if (handle.Instance == TIM8) {
        __HAL_RCC_TIM8_CLK_ENABLE();
        interruptTimers[7] = this;
        if (hasInterrupt) {
#if defined(STM32F2)||defined(STM32F4)||defined(STM32F7)||defined(STM32H7)
            HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);	
#else
            HAL_NVIC_SetPriority(TIM8_UP_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM8_UP_IRQn);
#endif
            HAL_NVIC_SetPriority(TIM8_CC_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);
        }

        TIM_ClockConfigTypeDef sClockSourceConfig;
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        HAL_TIM_ConfigClockSource(&handle, &sClockSourceConfig);

        TIM_MasterConfigTypeDef sMasterConfig;
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        HAL_TIMEx_MasterConfigSynchronization(&handle, &sMasterConfig);

        handle.Init.RepetitionCounter = 0;
    }
#endif
#ifdef TIM9
    if (handle.Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_ENABLE();
        interruptTimers[8] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
        }
    }
#endif
#ifdef TIM10
    if (handle.Instance == TIM10) {
        __HAL_RCC_TIM10_CLK_ENABLE();
        interruptTimers[9] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
        }
    }
#endif
#ifdef TIM11
    if (handle.Instance == TIM11) {
        __HAL_RCC_TIM11_CLK_ENABLE();
        interruptTimers[10] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
        }
    }
#elif defined(TIM21)
    if (handle.Instance == TIM21) {
        __HAL_RCC_TIM21_CLK_ENABLE();
        interruptTimers[10] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM21_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM21_IRQn);
        }
    }
#endif
#ifdef TIM12
    if (handle.Instance == TIM12) {
        __HAL_RCC_TIM12_CLK_ENABLE();
        interruptTimers[11] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
        }
    }
#elif defined(TIM22)
    if (handle.Instance == TIM22) {
        __HAL_RCC_TIM22_CLK_ENABLE();
        interruptTimers[11] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM22_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM22_IRQn);
        }
    }
#endif
#ifdef TIM13
    if (handle.Instance == TIM13) {
        __HAL_RCC_TIM13_CLK_ENABLE();
        interruptTimers[12] = this;
        if (hasInterrupt) {
            HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
        }
    }
#endif
#ifdef TIM15
    if (handle.Instance == TIM15) {
        __HAL_RCC_TIM15_CLK_ENABLE();
        interruptTimers[14] = this;		
        if (hasInterrupt) {
  #if defined(STM32H7)
            HAL_NVIC_SetPriority(TIM15_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM15_IRQn);  
  #else  
            HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
  #endif			
        }
    }
#endif
#ifdef TIM16
    if (handle.Instance == TIM16) {
        __HAL_RCC_TIM16_CLK_ENABLE();
        interruptTimers[15] = this;
        if (hasInterrupt) {
  #if defined(STM32H7)
            HAL_NVIC_SetPriority(TIM16_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM16_IRQn);  
  #else  
            HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
  #endif
        }
    }
#endif
#ifdef TIM17
    if (handle.Instance == TIM17) {
        __HAL_RCC_TIM17_CLK_ENABLE();
        interruptTimers[16] = this;
        if (hasInterrupt) {
  #if defined(STM32H7)
            HAL_NVIC_SetPriority(TIM17_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM17_IRQn);  
  #else  
            HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, TIM_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
  #endif
        }
    }
#endif
//add

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
	
    if ( channel &&(mode == TIMER_PWM)){
		resumePwm(channel);
	} else {
		resumeChannel(1);
		resumeChannel(2);
		resumeChannel(3);
		resumeChannel(4);
#if defined(TIM_CHANNEL_6) // Some chip(F3/7 L4 H7) there are 6 channels.  huaweiwx 2018.5.28
		resumeChannel(5);
		resumeChannel(6);
#endif
	}
}

int HardwareTimer::getChannel(int channel){
	if(channel == 1) return TIM_CHANNEL_1;
	if(channel == 2) return TIM_CHANNEL_2;
	if(channel == 3) return TIM_CHANNEL_3;
	if(channel == 4) return TIM_CHANNEL_4;
#if defined(TIM_CHANNEL_6) // Some chip(F3/7 L4 H7) there are 6 channels.  huaweiwx 2018.5.28
	if(channel == 5) return TIM_CHANNEL_5;
	if(channel == 6) return TIM_CHANNEL_6;
#endif
	return -1;
}

void HardwareTimer::resumePwm(int channel) {
	int timChannel = getChannel(channel);
	if(timChannel == -1) return;

	HAL_TIM_PWM_ConfigChannel(&handle, &channelOC[channel - 1], timChannel);
	HAL_TIM_PWM_Start(&handle, timChannel);
}

void HardwareTimer::resumeChannel(int channel) {
	int timChannel = getChannel(channel);
	if(timChannel == -1) return;

    if (channelOC[channel - 1].OCMode != OCMODE_NOT_USED) {
        HAL_TIM_OC_ConfigChannel(&handle, &channelOC[channel - 1], timChannel);
        if (callbacks[channel] != NULL) {
            HAL_TIM_OC_Start_IT(&handle, timChannel);
        } else {
            HAL_TIM_OC_Start(&handle, timChannel);
        }
    }

    if (channelIC[channel - 1].ICPolarity != OCMODE_NOT_USED) {
        HAL_TIM_IC_ConfigChannel(&handle, &channelIC[channel - 1], timChannel);

        if (callbacks[channel] != NULL) {
            HAL_TIM_IC_Start_IT(&handle, timChannel);
        } else {
            HAL_TIM_IC_Start(&handle, timChannel);
        }
    }
}

uint32_t HardwareTimer::getPrescaleFactor() {
    return handle.Init.Prescaler;
}

void HardwareTimer::setPrescaleFactor(uint32_t prescaler) {
    handle.Init.Prescaler = prescaler;
}

uint32_t HardwareTimer::getOverflow() {
    return handle.Init.Period;
}

void HardwareTimer::setOverflow(uint32_t overflow) {
    handle.Init.Period = overflow;
}

uint32_t HardwareTimer::getCount(void) {
    return __HAL_TIM_GET_COUNTER(&handle);
}

void HardwareTimer::setCount(uint32_t counter) {
    __HAL_TIM_SET_COUNTER(&handle, counter);
}

#define MAX_RELOAD ((1 << 16) - 1) // Not always! 32 bit timers!

uint32_t HardwareTimer::getBaseFrequency() {
#if defined(STM32F0)
    return HAL_RCC_GetPCLK1Freq();
#elif defined(STM32L0)||defined(STM32L1)
    return HAL_RCC_GetHCLKFreq();   /* hclk/timdiv(default 1) */
#elif defined(STM32F3)
    if((handle.Instance == TIM2)||(handle.Instance == TIM3)||(handle.Instance == TIM4))
       return 2*HAL_RCC_GetPCLK1Freq();
    else
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

uint32_t HardwareTimer::setPeriod(uint32_t microseconds) {
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

static bool isSameChannel(int channel, uint8_t signal) {
    switch(signal) {
        case TIM_CH1:
        case TIM_CH1N:
            return channel == 1;
        case TIM_CH2:
        case TIM_CH2N:
            return channel == 2;
        case TIM_CH3:
        case TIM_CH3N:
            return channel == 3;
        case TIM_CH4:
        case TIM_CH4N:
            return channel == 4;
	}
    return false;
}

static const uint32_t PIN_NOT_USED = 0xFF;

void HardwareTimer::setMode(int channel, TIMER_MODES mode, uint8_t pin) {
    int pinMode = PIN_NOT_USED;
    int pull = GPIO_NOPULL;

    switch(mode) {
        case TIMER_PWM:
            channelOC[channel - 1].OCMode = TIM_OCMODE_PWM1;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_TIMING;
            break;

        case TIMER_OUTPUT_COMPARE_ACTIVE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_ACTIVE;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_INACTIVE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_ACTIVE;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_TOGGLE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_TOGGLE;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_PWM1:
            channelOC[channel - 1].OCMode = TIM_OCMODE_PWM1;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_PWM2:
            channelOC[channel - 1].OCMode = TIM_OCMODE_PWM2;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_FORCED_ACTIVE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_FORCED_ACTIVE;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_OUTPUT_COMPARE_FORCED_INACTIVE:
            channelOC[channel - 1].OCMode = TIM_OCMODE_FORCED_INACTIVE;
            pinMode = GPIO_MODE_AF_PP;
            break;

        case TIMER_INPUT_CAPTURE_RISING:
            channelIC[channel - 1].ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
            pinMode = GPIO_MODE_AF_PP;
            pull = GPIO_PULLDOWN;
            break;

        case TIMER_INPUT_CAPTURE_FALLING:
            channelIC[channel - 1].ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
            pinMode = GPIO_MODE_AF_PP;
            pull = GPIO_PULLDOWN;
            break;
		default:
		    break;
    }

    if (pinMode != PIN_NOT_USED) {
        for(int i=0; i<tim_pin_list_size; i++) {
            if (isSameChannel(channel, tim_pin_list[i].signalType)) {

                if (pin == TIMER_DEFAULT_PIN ||
                        (variant_pin_list[pin].port == tim_pin_list[i].port && variant_pin_list[pin].pinMask == tim_pin_list[i].pinMask)) {

                    stm32GpioClockEnable(tim_pin_list[i].port);

                    GPIO_InitTypeDef GPIO_InitStruct;
                    GPIO_InitStruct.Pin = tim_pin_list[i].pinMask;
                    GPIO_InitStruct.Mode = pinMode;
                    GPIO_InitStruct.Pull = pull;
                    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

                    #ifdef STM32F1
                        tim_pin_list[i].alternate();
                    #else
                        GPIO_InitStruct.Alternate = tim_pin_list[i].alternate;
                    #endif

                    HAL_GPIO_Init(tim_pin_list[i].port, &GPIO_InitStruct);

                    return;
                }
            }
        }
    }
}

void HardwareTimer::setCompare(int channel, uint32_t compare) {
    channelOC[channel - 1].Pulse = compare;
}

uint32_t HardwareTimer::getCompare(int channel) {
    if (channel == 1) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_1);
    if (channel == 2) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_2);
    if (channel == 3) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_3);
    if (channel == 4) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_4);
#if defined(TIM_CHANNEL_6) // Some chip(F3/7 L4 H7) there are 6 channels.  huaweiwx 2018.5.28
    if (channel == 5) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_5);
    if (channel == 6) return __HAL_TIM_GET_COMPARE(&handle, TIM_CHANNEL_6);
#endif

    return 0;
}

void HardwareTimer::attachInterrupt(void (*callback)(void)) {
    callbacks[0] = callback;
}

void HardwareTimer::detachInterrupt() {
    callbacks[0] = NULL;
}

void HardwareTimer::attachInterrupt(int channel, void (*callback)(void)) {
    callbacks[channel] = callback;
}

void HardwareTimer::detachInterrupt(int channel) {
    callbacks[channel] = NULL;
}

void HardwareTimer::refresh() {
    HAL_TIM_GenerateEvent(&handle, TIM_EVENTSOURCE_UPDATE);
}

static void handleInterrupt(HardwareTimer *timer) {
    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_UPDATE) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_UPDATE);
        if (timer->callbacks[0] != NULL) timer->callbacks[0]();
    }

    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_CC1) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_CC1);
        if (timer->callbacks[1] != NULL) timer->callbacks[1]();
    }

    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_CC2) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_CC2);
        if (timer->callbacks[2] != NULL) timer->callbacks[2]();
    }

    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_CC3) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_CC3);
        if (timer->callbacks[3] != NULL) timer->callbacks[3]();
    }

    if(__HAL_TIM_GET_FLAG(&timer->handle, TIM_FLAG_CC4) != RESET) {
        __HAL_TIM_CLEAR_IT(&timer->handle, TIM_IT_CC4);
        if (timer->callbacks[4] != NULL) timer->callbacks[4]();
    }
//channel 5/6 not it interrupt	
}

#ifdef TIM1
    HardwareTimer Timer1(TIM1, chip_tim1, sizeof(chip_tim1) / sizeof(chip_tim1[0]));
#endif
#ifdef TIM2
    HardwareTimer Timer2(TIM2, chip_tim2, sizeof(chip_tim2) / sizeof(chip_tim2[0]));
#endif
#ifdef TIM3
    HardwareTimer Timer3(TIM3, chip_tim3, sizeof(chip_tim3) / sizeof(chip_tim3[0]));
#endif
#ifdef TIM4
    HardwareTimer Timer4(TIM4, chip_tim4, sizeof(chip_tim4) / sizeof(chip_tim4[0]));
#endif
#ifdef TIM5
    HardwareTimer Timer5(TIM5, chip_tim5, sizeof(chip_tim5) / sizeof(chip_tim5[0]));
#endif
#ifdef TIM8
    HardwareTimer Timer8(TIM8, chip_tim8, sizeof(chip_tim8) / sizeof(chip_tim8[0]));
#endif
#ifdef TIM9
    HardwareTimer Timer9(TIM9, chip_tim9, sizeof(chip_tim9) / sizeof(chip_tim9[0]));
#endif
#ifdef TIM10
    HardwareTimer Timer10(TIM10, chip_tim10, sizeof(chip_tim10) / sizeof(chip_tim10[0]));
#endif
#ifdef TIM11
    HardwareTimer Timer11(TIM11, chip_tim11, sizeof(chip_tim11) / sizeof(chip_tim11[0]));
#elif defined(TIM21)	/*L0 only not TIM11*/
    HardwareTimer Timer21(TIM21, chip_tim21, sizeof(chip_tim21) / sizeof(chip_tim21[0]));	
#endif
#ifdef TIM12
    HardwareTimer Timer12(TIM12, chip_tim12, sizeof(chip_tim12) / sizeof(chip_tim12[0]));
#elif defined(TIM22)	/*L0 only not TIM12*/
    HardwareTimer Timer22(TIM22, chip_tim22, sizeof(chip_tim22) / sizeof(chip_tim22[0]));	
#endif
#ifdef TIM13
    HardwareTimer Timer13(TIM13, chip_tim13, sizeof(chip_tim13) / sizeof(chip_tim13[0]));
#endif
#ifdef TIM14
    HardwareTimer Timer14(TIM14, chip_tim14, sizeof(chip_tim14) / sizeof(chip_tim14[0]));
#endif
#ifdef TIM15
    HardwareTimer Timer15(TIM15, chip_tim15, sizeof(chip_tim15) / sizeof(chip_tim15[0]));
#endif
#ifdef TIM16
    HardwareTimer Timer16(TIM16, chip_tim16, sizeof(chip_tim16) / sizeof(chip_tim16[0]));
#endif
#ifdef TIM17
    HardwareTimer Timer17(TIM17, chip_tim17, sizeof(chip_tim17) / sizeof(chip_tim17[0]));
#endif
//Timer interrupts:

extern "C" void TIM1_CC_IRQHandler(void) {
    if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
}

#if (STM32F410Cx || STM32F410Rx || STM32F410Tx)  /*F4 TIM1_UP_TIM10_IRQn. but F410 exception*/
	extern "C" void TIM1_UP_IRQHandler(void) {
		if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
	}
#elif defined(STM32F0)||defined(STM32F3)||defined(STM32L4)|| defined(STM32F100xB)|| defined(STM32F100xE) /*F100 TIM1_UP_TIM16*/
    extern "C" void TIM1_BRK_TIM15_IRQHandler(void) {
        if (interruptTimers[14] != NULL) handleInterrupt(interruptTimers[14]);
    }
    extern "C" void TIM1_UP_TIM16_IRQHandler(void) {
        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[15] != NULL) handleInterrupt(interruptTimers[15]);
    }
    extern "C" void TIM1_TRG_COM_TIM17_IRQHandler(void) {
        if (interruptTimers[16] != NULL) handleInterrupt(interruptTimers[16]);
    }
#elif defined(STM32F2)||defined(STM32F4)||defined(STM32F7)||defined(STM32H7)||defined(STM32L1)  /*F4  TIM1_UP_TIM10 or TIM1_UP*/
    extern "C" void TIM1_BRK_TIM9_IRQHandler(void) {
//        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[8] != NULL) handleInterrupt(interruptTimers[8]);
    }
    extern "C" void TIM1_UP_TIM10_IRQHandler(void) {
        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[9] != NULL) handleInterrupt(interruptTimers[9]);
    }
    extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void) {
//        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[10] != NULL) handleInterrupt(interruptTimers[10]);
    }
#elif defined(STM32F1)/*F101/103/105/107  TIM1_UP_TIM10 or TIM1_UP*/
    extern "C" void TIM1_BRK_TIM9_IRQHandler(void) {
        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[9] != NULL) handleInterrupt(interruptTimers[9]);
    }
    extern "C" void TIM1_UP_TIM10_IRQHandler(void) {
        if (interruptTimers[0] != NULL) handleInterrupt(interruptTimers[0]);
        if (interruptTimers[9] != NULL) handleInterrupt(interruptTimers[9]);
    }
#endif


// in stm32_PWM.c
/*
extern "C" void TIM3_IRQHandler(void) {
    handleInterrupt(interruptTimers[2]);
}*/

#ifdef TIM3  /*priority to use TIM3. huaweiwx@sina.com 2018.2.2*/
// in stm32_PWM.c if have not TIM3 use TIM2 define 
extern "C" void TIM2_IRQHandler(void) {
    if (interruptTimers[1] != NULL) handleInterrupt(interruptTimers[1]);
}
#endif

extern "C" void TIM4_IRQHandler(void) {
    if (interruptTimers[3] != NULL) handleInterrupt(interruptTimers[3]);
}

//TIM5/8 add by huaweiwx 
#ifdef TIM5
extern "C" void TIM5_IRQHandler(void) {
    if (interruptTimers[4] != NULL) handleInterrupt(interruptTimers[4]);
}
#endif

#ifdef TIM8
extern "C" void TIM8_CC_IRQHandler(void) {
    if (interruptTimers[7] != NULL) handleInterrupt(interruptTimers[7]);
}

#if defined(STM32F2)||defined(STM32F4)||defined(STM32F7)||defined(STM32H7)||defined(STM32L1)
extern "C" void TIM8_BRK_TIM12_IRQHandler(void) {
//    if (interruptTimers[7] != NULL) handleInterrupt(interruptTimers[7]);
    if (interruptTimers[11] != NULL) handleInterrupt(interruptTimers[11]);
}

extern "C" void TIM8_UP_TIM13_IRQHandler(void) {
    if (interruptTimers[7] != NULL) handleInterrupt(interruptTimers[7]);
    if (interruptTimers[12] != NULL) handleInterrupt(interruptTimers[12]);
}
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler(void) {
//    if (interruptTimers[7] != NULL) handleInterrupt(interruptTimers[7]);
    if (interruptTimers[13] != NULL) handleInterrupt(interruptTimers[13]);
}
#else
extern "C" void TIM8_UP_IRQHandler(void) {
    if (interruptTimers[7] != NULL) handleInterrupt(interruptTimers[7]);
}
#endif
#endif //TIM8

#if defined(STM32H7)
#ifdef TIM15
    extern "C" void TIM15_IRQHandler(void) {
        if (interruptTimers[14] != NULL) handleInterrupt(interruptTimers[14]);
    }
#endif	
#ifdef TIM16
    extern "C" void TIM16_IRQHandler(void) {
        if (interruptTimers[15] != NULL) handleInterrupt(interruptTimers[15]);
    }
#endif	
#ifdef TIM17
    extern "C" void TIM17_IRQHandler(void) {
        if (interruptTimers[16] != NULL) handleInterrupt(interruptTimers[16]);
    }
#endif
#endif

//L0 only
#ifdef TIM21
extern "C" void TIM21_IRQHandler(void) {
    if (interruptTimers[10] != NULL) handleInterrupt(interruptTimers[10]); 
}
#endif
#ifdef TIM22
extern "C" void TIM22_IRQHandler(void) {
    if (interruptTimers[11] != NULL) handleInterrupt(interruptTimers[11]); 
}
#endif