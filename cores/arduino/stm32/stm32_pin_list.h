#ifndef STM32_PIN_LIST_H
#define STM32_PIN_LIST_H

#include "variant.h"
#include "stm32_HAL/stm32XXxx_ll_gpio.h"

#ifdef VARIANT_PIN_LIST
# define PIN_LIST VARIANT_PIN_LIST
#else
# define PIN_LIST CHIP_PIN_LIST
#endif

#ifdef __cplusplus

class __ConstPin {
  public:
    constexpr __ConstPin(const int ulPortBase, const int pinMask, const int ucPin): ulPortBase(ulPortBase), pinMask(pinMask), ucPin(ucPin) {};
    constexpr operator int() const {
      return ucPin;
    }
    const int ulPortBase;
    const int pinMask;
    const int ucPin;
};

#define PIN(a, b) __P##a##b
enum {
  PIN_LIST
  NUM_DIGITAL_PINS,
};
#undef PIN

#if 1 //ndef STM32H7
#define PIN(a, b) P##a##b(GPIO##a##_BASE,LL_GPIO_PIN_##b,__P##a##b)
#else
#define PIN(a, b) P##a##b(GPIO##a##_BASE,GPIO_PIN_##b,__P##a##b)
#endif
constexpr __ConstPin PIN_LIST __IGNORE(0, 0, -1);
#undef PIN

#if USE_AVREMULATION > 0   /*avr Pa_b*/
#if 1 // ndef STM32H7
#define PIN(a, b) P##a##_##b(GPIO##a##_BASE,LL_GPIO_PIN_##b,__P##a##b)
#else
#define PIN(a, b) P##a##_##b(GPIO##a##_BASE,GPIO_PIN_##b,__P##a##b)
#endif
constexpr __ConstPin PIN_LIST _IGNORE(0, 0, -1);
#undef PIN
#endif

#define ARDUINOPIN_TypeDef  __ConstPin

#else
	
#define ARDUINOPIN_TypeDef  uint8_t

#define PIN(a, b) P ## a ## b
enum {
  PIN_LIST
  NUM_DIGITAL_PINS,
};
#undef PIN

#if USE_AVREMULATION > 0   /*avr PORTx PINx DDRx emulation*/
#define PIN(a, b) P ## a ## _ ## b
enum {
  PIN_LIST
};
#undef PIN
#endif

#endif  //__cplusplus

#endif  //STM32_PIN_LIST_H
