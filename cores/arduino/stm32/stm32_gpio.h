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

#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include "stm32_def.h"
#include "stm32_pin_list.h"
#include "variant.h"
#include "stm32_HAL/stm32XXxx_ll_gpio.h"

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3

#define OUTPUT_PP 0x1    /* as OUTPUT add by huaweiwx@sina.com 2017.6.9   */
#define OUTPUT_OD 0x11   /*!< Output Open Drain Mode  add by huaweiwx@sina.com 2017.6.9   */

#ifndef GPIO_SPEED_FREQ_VERY_HIGH
    #define GPIO_SPEED_FREQ_VERY_HIGH GPIO_SPEED_FREQ_HIGH
#endif

#define RwReg uint32_t

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
    GPIO_TypeDef *port;
    uint32_t pinMask;
} stm32_port_pin_type;

typedef uint32_t (*stm32_clock_freq_func)();

typedef struct {
    void *instance;
    stm32_clock_freq_func clock_freq_func;
} stm32_clock_freq_list_type;

extern const stm32_port_pin_type variant_pin_list[NUM_DIGITAL_PINS];

inline GPIO_TypeDef* pinToPort(uint8_t pin){return variant_pin_list[pin].port;}  /* equal_to digitalPinToPort(pin)*/
inline uint32_t pinToBitMask(uint8_t pin){return variant_pin_list[pin].pinMask;} /* equal_to digitalPinToBitMask(pin)*/

/**
 * Start clock for the fedined port
 */
void stm32GpioClockEnable(GPIO_TypeDef *port);

/**
 * If PWM is used at least once, this method is set to the PWM disable function in stm32_PWM.c
 */
typedef void (*stm32_pwm_disable_callback_func)(GPIO_TypeDef *port, uint32_t pin);
extern stm32_pwm_disable_callback_func stm32_pwm_disable_callback;

extern void attachInterrupt(uint8_t, void (*)(void), int mode);
extern void detachInterrupt(uint8_t);

inline void digitalWrite(uint8_t pin, uint8_t value) {
//    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
//        return;
//    }
    
    stm32_port_pin_type port_pin = variant_pin_list[pin];
    HAL_GPIO_WritePin(port_pin.port, port_pin.pinMask, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


inline int digitalRead(uint8_t pin) {
//    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
//        return 0;
//    }
    
    stm32_port_pin_type port_pin = variant_pin_list[pin];
    return HAL_GPIO_ReadPin(port_pin.port, port_pin.pinMask);
}

//add by huaweiwx@sina.com  2017.6.4
inline void digitalToggle(uint8_t pin) {
//    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
//       return;
//    }
    stm32_port_pin_type port_pin = variant_pin_list[pin];
    HAL_GPIO_TogglePin(port_pin.port, port_pin.pinMask);
}

#ifdef __cplusplus
}
#endif


///////////////////////////////
// The following functions are meant to be used with compile time constant parameters
#define PIN(a, b)   b
static const uint8_t variant_gpiopin_pos_static[] = {
   PIN_LIST
};  
#undef PIN
 
#define PIN(a, b)   GPIO##a##_BASE
static const uint32_t variant_gpiopin_base_static[] = {
  PIN_LIST
};  
#undef PIN

#ifndef STM32H7
#define PIN(a, b) { GPIO##a , LL_GPIO_PIN_##b }
static const stm32_port_pin_type variant_pin_list_ll_static[] = {
  PIN_LIST
};
#undef PIN
#endif

#ifdef __cplusplus

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
inline constexpr const uint8_t  pinMaskPos(__ConstPin pin){return variant_gpiopin_pos_static[pin];}
inline constexpr const uint32_t pinToBase(__ConstPin pin){return variant_gpiopin_base_static[pin];}

#if defined(STM32H7)
  inline constexpr const uint32_t pinToBitMask(__ConstPin pin){return (1<< pinMaskPos(pin));} /* equal_to digitalPinToBitMask(pin)*/
#else
  inline constexpr const uint32_t pinTollBitMask(__ConstPin pin){return variant_pin_list_ll_static[pin].pinMask;} 	
 #if defined(STM32F1)
    inline constexpr const uint32_t pinToBitMask(__ConstPin pin){return ((variant_pin_list_ll_static[pin].pinMask>>8)&0xffff);}/* equal_to digitalPinToBitMask(pin)*/
 #else
    inline constexpr const uint32_t pinToBitMask(__ConstPin pin){return (variant_pin_list_ll_static[pin].pinMask);} /* equal_to digitalPinToBitMask(pin)*/
 #endif
#endif

#pragma GCC diagnostic pop

inline constexpr const GPIO_TypeDef* pinToPort(__ConstPin pin){return (GPIO_TypeDef *)pinToBase(pin);}

inline void digitalWrite(__ConstPin pin, uint8_t value) {
#ifdef STM32H7
    if(value != GPIO_PIN_RESET)
    {
      ((GPIO_TypeDef *)pinToPort(pin))->BSRRL = pinToBitMask(pin);
    }else{
      ((GPIO_TypeDef *)pinToPort(pin))->BSRRH = pinToBitMask(pin) ;
    }
#else	
    if (value) {
        LL_GPIO_SetOutputPin(variant_pin_list_ll_static[pin].port, variant_pin_list_ll_static[pin].pinMask);
    } else {
        LL_GPIO_ResetOutputPin(variant_pin_list_ll_static[pin].port, variant_pin_list_ll_static[pin].pinMask);
    }
#endif	
}

inline int digitalRead(__ConstPin pin) {
#ifdef STM32H7
    return (((GPIO_TypeDef *)pinToPort(pin))->IDR & pinToBitMask(pin))?1:0;
//    return HAL_GPIO_ReadPin((GPIO_TypeDef *)pinToPort(pin), pinToBitMask(pin));
#else	
    return LL_GPIO_IsInputPinSet(variant_pin_list_ll_static[pin].port, variant_pin_list_ll_static[pin].pinMask);
#endif
}


#ifdef STM32H7
inline static void pinMode(__ConstPin pin, uint8_t mode) {
     pinMode((uint8_t)pin,mode);
}
#else
extern "C" void pinModeLL(GPIO_TypeDef *port, uint32_t ll_pin, uint8_t mode);
inline static void pinMode(__ConstPin pin, uint8_t mode) {
    pinModeLL(variant_pin_list_ll_static[pin].port, variant_pin_list_ll_static[pin].pinMask, mode);
}
#endif

//add by huaweiwx@sina.com  2017.6.4
inline void digitalToggle(__ConstPin pin) {
#ifdef STM32H7
    ((GPIO_TypeDef *)pinToPort(pin))->ODR  ^=  pinToBitMask(pin);
#else
    LL_GPIO_TogglePin(variant_pin_list_ll_static[pin].port, variant_pin_list_ll_static[pin].pinMask);
#endif
}

//add by huaweiwx@sina.com  2018.2.7
template<class T> 
inline void operator << (__ConstPin co, T value){
  digitalWrite(co, (uint8_t)value);
}

inline void operator << (__ConstPin co, __ConstPin ci){
  digitalWrite(co, (uint8_t)digitalRead(ci));
}

template<class T> 
inline void operator >> (__ConstPin ci, T &value) {
  value = digitalRead(ci);
}

inline void operator >> (__ConstPin ci, __ConstPin co){
  digitalWrite(co, (uint8_t)digitalRead(ci));
}

#endif //__cplusplus


#endif //STM32_GPIO_H
