/*
  2018.5.18  add TIM5/8~17 by huaweiwx
  2018.5.28  for F3/F7/L4/H7 support channel5&6 by huaweiwx
*/

#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_

#include <Arduino.h>
#include "stm32_gpio_af.h"

#if defined(TIM_CHANNEL_6) // Some chip(F3/7 L4 H7) there are 6 channels.  huaweiwx 2018.5.28
#define  TIMER_CHANNELS 6
#else
#define  TIMER_CHANNELS 4
#endif

typedef enum {
    //libmaple:                             // HAL compatible
    TIMER_DISABLED,
    TIMER_PWM,                              // == TIM_OCMODE_PWM1
    TIMER_OUTPUT_COMPARE,                   // == TIM_OCMODE_TIMING           no output, useful for only-interrupt

    //other:
    TIMER_OUTPUT_COMPARE_ACTIVE,            // == TIM_OCMODE_ACTIVE           pin is set high when counter == channel compare
    TIMER_OUTPUT_COMPARE_INACTIVE,          // == TIM_OCMODE_INACTIVE         pin is set low when counter == channel compare
    TIMER_OUTPUT_COMPARE_TOGGLE,            // == TIM_OCMODE_TOGGLE           pin toggles when counter == channel compare
    TIMER_OUTPUT_COMPARE_PWM1,              // == TIM_OCMODE_PWM1             pin high when counter < channel compare, low otherwise
    TIMER_OUTPUT_COMPARE_PWM2,              // == TIM_OCMODE_PWM2             pin low when counter < channel compare, high otherwise
    TIMER_OUTPUT_COMPARE_FORCED_ACTIVE,     // == TIM_OCMODE_FORCED_ACTIVE    pin always high
    TIMER_OUTPUT_COMPARE_FORCED_INACTIVE,   // == TIM_OCMODE_FORCED_INACTIVE  pin always low

    //Input capture
    TIMER_INPUT_CAPTURE_RISING,          // == TIM_INPUTCHANNELPOLARITY_RISING
    TIMER_INPUT_CAPTURE_FALLING,         // == TIM_INPUTCHANNELPOLARITY_FALLING

    //PWM input capture on channel 1 + channel 2
    //TIMER_INPUT_CAPTURE_PWM,             // == TIM_INPUTCHANNELPOLARITY_RISING (channel 1) + TIM_INPUTCHANNELPOLARITY_FALLING (channel 2)

    //Encoder mode
    //TIMER_ENCODER                        // == TIM_ENCODERMODE_TI1
} TIMER_MODES;

#define TIMER_DEFAULT_PIN 0xFF

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

class HardwareTimer {
public:
    HardwareTimer(TIM_TypeDef *instance, const stm32_tim_pin_list_type *pin_list, int pin_list_size = 0);

    void pause(void);

    void resume(int channel = 0, TIMER_MODES mode = TIMER_DISABLED);

    uint32_t getPrescaleFactor();

    void setPrescaleFactor(uint32_t factor);

    uint32_t getOverflow();

    void setOverflow(uint32_t val);

    uint32_t getCount(void);

    void setCount(uint32_t val);

    uint32_t setPeriod(uint32_t microseconds);

    void setMode(int channel, TIMER_MODES mode, uint8_t pin = TIMER_DEFAULT_PIN);

    uint32_t getCompare(int channel);

    void setCompare(int channel, uint32_t compare);

    //Add interrupt to period update
    void attachInterrupt(void (*handler)(void));

    void detachInterrupt();

    //Add interrupt to channel
    void attachInterrupt(int channel, void (*handler)(void));

    void detachInterrupt(int channel);

    void refresh(void);

    uint32_t getBaseFrequency();

    TIM_HandleTypeDef handle = {0};

    TIM_OC_InitTypeDef channelOC[TIMER_CHANNELS];

    TIM_IC_InitTypeDef channelIC[TIMER_CHANNELS];
	
    //Callbacks: 0 for update, 1-4 for channels
    void (*callbacks[5])(void);

    const stm32_tim_pin_list_type *tim_pin_list;

    int tim_pin_list_size;

private:
    int  getChannel(int channel);
    void resumeChannel(int channel);
    void resumePwm(int channel);
};

#pragma GCC diagnostic pop

#ifdef TIM1
    extern HardwareTimer Timer1;
#endif

#ifdef TIM2
    extern HardwareTimer Timer2;
#endif

#ifdef TIM3
    extern HardwareTimer Timer3;
#endif

#ifdef TIM4
    extern HardwareTimer Timer4;
#endif

#ifdef TIM5
    extern HardwareTimer Timer5;
#endif

#ifdef TIM8
    extern HardwareTimer Timer8;
#endif

//F2/4/7 H7 L1
#ifdef TIM9
    extern HardwareTimer Timer9;
#endif
#ifdef TIM10
    extern HardwareTimer Timer10;
#endif
#ifdef TIM11
    extern HardwareTimer Timer11;
#elif defined(TIM21)	/*L0 only*/
    extern HardwareTimer Timer21;
#endif
#ifdef TIM12
    extern HardwareTimer Timer12;
#elif defined(TIM22)	/*L0 only*/
    extern HardwareTimer Timer22;
#endif
#ifdef TIM13
    extern HardwareTimer Timer13;
#endif
#ifdef TIM14
    extern HardwareTimer Timer13;
#endif

// F0/3 L4 H7
#ifdef TIM15
    extern HardwareTimer Timer15;
#endif
#ifdef TIM16
    extern HardwareTimer Timer16;
#endif
#ifdef TIM17
    extern HardwareTimer Timer17;
#endif

#endif //HARDWARETIMER_H_
