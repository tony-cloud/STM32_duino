#ifndef STM32_DEF_H
#define STM32_DEF_H

#include "stm32_build_defines.h"

#ifdef STM32F0
    #include "stm32f0xx.h"
    #include "stm32f0xx_hal.h"
#elif defined(STM32F1)
    #include "stm32f1xx.h"
    #include "stm32f1xx_hal.h"
#elif defined(STM32F2)
    #include "stm32f2xx.h"
    #include "stm32f2xx_hal.h"
#elif defined(STM32F3)
    #include "stm32f3xx.h"
    #include "stm32f3xx_hal.h"
#elif defined(STM32F4)
    #include "stm32f4xx.h"
    #include "stm32f4xx_hal.h"
#elif defined(STM32F7)
    #include "stm32f7xx.h"
    #include "stm32f7xx_hal.h"
#elif defined(STM32L0)
    #include "stm32l0xx.h"
    #include "stm32l0xx_hal.h"
#elif defined(STM32L1)
    #include "stm32l1xx.h"
    #include "stm32l1xx_hal.h"
#elif defined(STM32L4)
    #include "stm32l4xx.h"
    #include "stm32l4xx_hal.h"
#else
    #error "STM32XX is not defined in boards.txt"
#endif

#if __has_include("halSketchConfig.h")
 #include "halSketchConfig.h"
#endif

//default defines,  overriden by halDefaultConfig.h in sketch path
//OS
#ifndef FREERTOS
#define FREERTOS    0
#endif

#ifndef UCOSII
#define UCOSII      0
#endif

#ifndef USERMAIN
#define USERMAIN    0
#endif

#ifndef BOOTLOADER
#define BOOTLOADER  0
#endif


//default
//PRIORITY 
//Cortex-M0/3/4/7 Processor Exceptions
#ifndef CORTEX_INT_PRIORITY
 #define CORTEX_INT_PRIORITY 0
#endif

#if defined(STM32F0)||defined(STM32L0)

#ifndef SYSTICK_INT_PRIORITY
 #if FREERTOS
  #define SYSTICK_INT_PRIORITY 15
 #else
  #define SYSTICK_INT_PRIORITY 0	
 #endif
#endif


//STN32 specific Interrupt
#ifndef STM32_INT_PRIORITY
 #define STM32_INT_PRIORITY	2
#endif

#ifndef TAMPER_PRIORITY
 #define TAMPER_PRIORITY  2
#endif
#ifndef RTC_PRIORITY
 #define RTC_PRIORITY     2
#endif
#ifndef RCC_PRIORITY
 #define RCC_PRIORITY     2
#endif
#ifndef EXTI_PRIORITY
 #define EXTI_PRIORITY    3
#endif
#ifndef DMA_PRIORITY
 #define DMA_PRIORITY     2
#endif
#ifndef ADC_PRIORITY
 #define ADC_PRIORITY     2
#endif
#ifndef USB_HP_PRIORITY
 #define USB_HP_PRIORITY  2
#endif
#ifndef USB_LP_PRIORITY
 #define USB_LP_PRIORITY  2
#endif
#ifndef TIM_PRIORITY
 #define TIM_PRIORITY     2
#endif
#ifndef I2C_PRIORITY
 #define I2C_PRIORITY     2
#endif
#ifndef SPI_PRIORITY
 #define SPI_PRIORITY     2
#endif
#ifndef USART_PRIORITY
 #define USART_PRIORITY   2
#endif
#ifndef SDIO_PRIORITY
 #define SDIO_PRIORITY    2
#endif

#else  //F1/2/3/4/7 L1/4

#ifndef SYSTICK_INT_PRIORITY
 #if FREERTOS
  #define SYSTICK_INT_PRIORITY 15
 #else
  #define SYSTICK_INT_PRIORITY 0	
 #endif
#endif

#ifndef STM32_INT_PRIORITY
#define STM32_INT_PRIORITY     5
#endif
#ifndef TAMPER_PRIORITY
#define TAMPER_PRIORITY  5
#endif
#ifndef RTC_PRIORITY
#define RTC_PRIORITY     5
#endif
#ifndef RCC_PRIORITY
#define RCC_PRIORITY     5
#endif
#ifndef EXTI_PRIORITY
#define EXTI_PRIORITY    15  //botton  use 0x0f
#endif
#ifndef DMA_PRIORITY
#define DMA_PRIORITY     5
#endif
#ifndef ADC_PRIORITY
#define ADC_PRIORITY     5
#endif
#ifndef USB_HP_PRIORITY
#define USB_HP_PRIORITY  5
#endif
#ifndef USB_LP_PRIORITY
#define USB_LP_PRIORITY  5
#endif
#ifndef TIM_PRIORITY
#define TIM_PRIORITY     5
#endif
#ifndef I2C_PRIORITY
#define I2C_PRIORITY     5
#endif
#ifndef SPI_PRIORITY
#define SPI_PRIORITY     5
#endif
#ifndef USART_PRIORITY
#define USART_PRIORITY   5
#endif
#ifndef SDIO_PRIORITY
#define SDIO_PRIORITY    5
#endif

#endif


#endif
