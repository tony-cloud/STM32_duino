/*
  2018.5.28  fock from Daniel Fekete HardwareTimer lib and add basic timer TIM6/7 by huaweiwx
*/

#ifndef _HARDWAREBASETIMER_H_
#define _HARDWAREBASETIMER_H_

#include <Arduino.h>
#include "stm32_gpio_af.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

class HardwareBaseTimer {
public:
    HardwareBaseTimer(TIM_TypeDef *instance){
	   handle.Instance = instance;
	};

    void pause(void) {
		HAL_TIM_Base_Stop(&handle);
    };

    void resume(void);

    uint32_t getPrescaleFactor();

    void setPrescaleFactor(uint32_t factor);

    uint32_t getOverflow();

    void setOverflow(uint32_t val);

    uint32_t getCount(void);

    void setCount(uint32_t val);

    uint32_t setPeriod(uint32_t microseconds);

    void attachInterrupt(void (*handler)(void)) {
		callbacks[0] = handler;
	}

    void detachInterrupt() {
		callbacks[0] = NULL;
	};

    void refresh(void){
       HAL_TIM_GenerateEvent(&handle, TIM_EVENTSOURCE_UPDATE);
	};

    uint32_t getBaseFrequency();

    TIM_HandleTypeDef handle = {0};

    //Callbacks: 0 for update, 1-4 for channels
    void (*callbacks[1])(void);

};

#pragma GCC diagnostic pop

#if defined(TIM6)||defined(TIM7)
#ifdef TIM6
    extern HardwareBaseTimer Timer6;
#endif

#ifdef TIM7
  #if FREERTOS == 0 
    extern HardwareBaseTimer Timer7;
  #endif	
#endif
#else
 #error !!! This chip have not TIM6 or TIM7 !!!
#endif

#endif //HARDWARETIMER_H_
