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
  
  modify by huaweiwx@sina.com 2018.2.2
*/

#include "stm32_gpio.h"

TIM_HandleTypeDef *handle;

#define min(a,b) ((a)<(b)?(a):(b))
#define PWM_FREQUENCY_HZ  1000

static uint32_t counter;
static uint32_t waitCycles;
static uint8_t analogWriteResolutionBits = 8;
static uint32_t pwmFrequecyHz = PWM_FREQUENCY_HZ;  //add by huaweiwx@sina.com 2017.8.2
const uint32_t TIMER_MAX_CYCLES = UINT16_MAX;

extern void pinMode(uint8_t, uint8_t);

stm32_pwm_disable_callback_func stm32_pwm_disable_callback = NULL;

void (*pwm_callback_func)();

void pwm_callback();

typedef struct {
    GPIO_TypeDef *port;
    void (*callback)();
    uint32_t pinMask;
    uint32_t waveLengthCycles;
    uint32_t dutyCycle;
    int32_t counterCycles;
} stm32_pwm_type;

static stm32_pwm_type pwm_config[sizeof(variant_pin_list) / sizeof(variant_pin_list[0])];

void stm32_pwm_disable(GPIO_TypeDef *port, uint32_t pin);

void analogWriteResolution(int bits) {
    analogWriteResolutionBits = bits;
}
uint8_t getAnalogWriteResolution(void) {
    return analogWriteResolutionBits;
}

static void initTimer(){
    static TIM_HandleTypeDef staticHandle;

    if (handle == NULL) {
        handle = &staticHandle;
        pwm_callback_func = &pwm_callback;

        stm32_pwm_disable_callback = &stm32_pwm_disable;


        #ifdef TIM3  /*some TIM2 is 32bit, priority to use TIM3. huaweiwx@sina.com 2018.2.2*/
            __HAL_RCC_TIM3_CLK_ENABLE();
            HAL_NVIC_SetPriority(TIM3_IRQn, TIM_PRIORITY, 0); //TIM_PRIORITY define in stm32_def.h huaweiwx@sina.com 2017.12
            HAL_NVIC_EnableIRQ(TIM3_IRQn);

            handle->Instance = TIM3;
        #else  //99% of chips have TIM2
            __HAL_RCC_TIM2_CLK_ENABLE();
            HAL_NVIC_SetPriority(TIM2_IRQn, TIM_PRIORITY, 0); //TIM_PRIORITY define in stm32_def.h huaweiwx@sina.com 2017.12
            HAL_NVIC_EnableIRQ(TIM2_IRQn);

            handle->Instance = TIM2;
        #endif

        handle->Init.Prescaler = 0;
        handle->Init.CounterMode = TIM_COUNTERMODE_UP;
        waitCycles = TIMER_MAX_CYCLES;
        handle->Init.Period = waitCycles;
        handle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        HAL_TIM_Base_Init(handle);

        HAL_TIM_Base_Start_IT(handle);
    }
}


void pwmWrite(uint8_t pin, int dutyCycle, int frequency, int durationMillis) {
    initTimer();

    for(size_t i=0; i<sizeof(pwm_config) / sizeof(pwm_config[0]); i++) {
        if (pwm_config[i].port == NULL ||
                (pwm_config[i].port == variant_pin_list[pin].port
                && pwm_config[i].pinMask == variant_pin_list[pin].pinMask)) {

            if (pwm_config[i].port == NULL) {
                pinMode(pin, OUTPUT);
            }
#ifdef STM32F0  // there is no pclk2
			uint32_t timerFreq = HAL_RCC_GetPCLK1Freq();
#else
			uint32_t timerFreq = HAL_RCC_GetPCLK2Freq();
#endif
            pwm_config[i].port = variant_pin_list[pin].port;
            pwm_config[i].pinMask = variant_pin_list[pin].pinMask;
            pwm_config[i].waveLengthCycles = timerFreq / frequency;
		    pwm_config[i].dutyCycle = (uint64_t)pwm_config[i].waveLengthCycles * dutyCycle >> 16;

            if (durationMillis > 0) {
                pwm_config[i].counterCycles = timerFreq / 1000 * durationMillis;
            }

            break;
        }
    }
}

extern void tone(uint8_t pin, unsigned int frequency, unsigned long durationMillis) {
	pwmWrite(pin, 1 << 15, frequency, durationMillis);
}

extern void noTone(uint8_t pin){
	stm32_port_pin_type port_pin = variant_pin_list[pin];
	stm32_pwm_disable(port_pin.port,port_pin.pinMask);
}

void analogWrite(uint8_t pin, int value) {
	pwmWrite(pin, ((uint32_t)value << 16) >> analogWriteResolutionBits, pwmFrequecyHz, 0); //add by huaweiwx@sina.com 2017.8.2
}

/*add huaweiwx@sina.com 2018.8.2*/
void setPwmFrequency(uint32_t freqHz){
    pwmFrequecyHz = freqHz;
}

uint32_t getPwmFrequency(void){
    return pwmFrequecyHz;
}

void stm32ScheduleMicros(uint32_t microseconds, void (*callback)()) {
    initTimer();

    for(size_t i=0; i<sizeof(pwm_config) / sizeof(pwm_config[0]); i++) {
        if (pwm_config[i].port == NULL && pwm_config[i].callback == NULL) {

            pwm_config[i].callback = callback;
#ifdef STM32F0  // there is no pclk2
            pwm_config[i].waveLengthCycles = HAL_RCC_GetPCLK1Freq() * (uint64_t)microseconds / 1000000;
#else
            pwm_config[i].waveLengthCycles = HAL_RCC_GetPCLK2Freq() * (uint64_t)microseconds / 1000000;
#endif
            pwm_config[i].counterCycles = pwm_config[i].waveLengthCycles;
            break;
        }
    }
}

void stm32_pwm_disable(GPIO_TypeDef *port, uint32_t pinMask) {
    for(size_t i=0; i<sizeof(pwm_config) / sizeof(pwm_config[0]); i++) {
        if (pwm_config[i].port == NULL) {
            return;
        }

        if (pwm_config[i].port == port && pwm_config[i].pinMask == pinMask) {

            for(size_t j = i + 1; j < sizeof(pwm_config) / sizeof(pwm_config[0]); j++) {
                if (pwm_config[j].port == NULL) {
                    pwm_config[i].port = pwm_config[j - 1].port;
                    pwm_config[i].pinMask = pwm_config[j - 1].pinMask;

                    pwm_config[j - 1].port = NULL;
                    break;
                }
            }

            break;
        }
    }
}

void pwm_callback() {
    if(__HAL_TIM_GET_FLAG(handle, TIM_FLAG_UPDATE) != RESET) {
        if(__HAL_TIM_GET_IT_SOURCE(handle, TIM_IT_UPDATE) !=RESET) {
            __HAL_TIM_CLEAR_IT(handle, TIM_IT_UPDATE);

            counter += waitCycles;
            uint32_t nextWaitCycles = TIMER_MAX_CYCLES;

            for(size_t i=0; i<sizeof(pwm_config); i++) {
                if (pwm_config[i].port != NULL) {
                    if (pwm_config[i].dutyCycle > counter % pwm_config[i].waveLengthCycles) {
                      #ifdef STM32H7
						pwm_config[i].port->BSRRL = pwm_config[i].pinMask;
					  #else
					    pwm_config[i].port->BSRR = pwm_config[i].pinMask;
					  #endif
                        nextWaitCycles = min(nextWaitCycles, pwm_config[i].dutyCycle - (counter % pwm_config[i].waveLengthCycles));
                    } else {
                      #ifdef STM32H7
						pwm_config[i].port->BSRRH = pwm_config[i].pinMask;
					  #else
                        pwm_config[i].port->BSRR = pwm_config[i].pinMask << 16;
					  #endif
                        nextWaitCycles = min(nextWaitCycles, pwm_config[i].waveLengthCycles - counter % pwm_config[i].waveLengthCycles);
                    }

                    if (pwm_config[i].counterCycles > 0) {
                        if (pwm_config[i].counterCycles <= (int)waitCycles) {
                            stm32_pwm_disable(pwm_config[i].port, pwm_config[i].pinMask);
                        } else {
                            pwm_config[i].counterCycles -= waitCycles;
                        }
                    }
                } else if (pwm_config[i].callback != NULL) {
                    pwm_config[i].counterCycles -= waitCycles;
                    if (pwm_config[i].counterCycles < 0) {
                        pwm_config[i].callback();
                        pwm_config[i].counterCycles += pwm_config[i].waveLengthCycles;
					}
				} else {
                    break;
                }
            }

            if (!nextWaitCycles || nextWaitCycles > TIMER_MAX_CYCLES) {
                nextWaitCycles = TIMER_MAX_CYCLES;
            }
            waitCycles = nextWaitCycles;

            __HAL_TIM_SET_AUTORELOAD(handle, waitCycles);
        }
    }
}

#ifdef TIM3  /*priority to use TIM3. huaweiwx@sina.com 2018.2.2*/
  extern void TIM3_IRQHandler(void) {
#else
  extern void TIM2_IRQHandler(void) {
#endif

    if (pwm_callback_func != NULL) {
        (*pwm_callback_func)();
    }
}
