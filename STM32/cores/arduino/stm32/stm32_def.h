#ifndef STM32_DEF_H
#define STM32_DEF_H

#include "stm32_build_defines.h"

#if __has_include("halSketchConfig.h")
 #include "halSketchConfig.h"
#endif

//default defines,  overriden by halSketchConfig.h in sketch path
//OS
#ifndef FREERTOS
#define FREERTOS    0
#endif

#ifndef UCOSII
#define UCOSII      0
#endif

#ifndef USERMAIN    //main.cpp
#define USERMAIN    0
#endif

#ifndef BOOTLOADER
#define BOOTLOADER  0
#endif

//USB
#ifndef USER_USBDCONF
#define USER_USBDCONF  0
#endif

#ifndef USER_USBDCDC
#define USER_USBDCDC  0
#endif

#ifndef USER_USBDMSC
#define USER_USBDMSC  0
#endif

#ifndef USER_USBDCOMPOSITE
#define USER_USBDCOMPOSITE  0
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
  #define SYSTICK_INT_PRIORITY	3
  #define STM32_INT_PRIORITY	2
 #else
  #define SYSTICK_INT_PRIORITY	0
  #define STM32_INT_PRIORITY	2
 #endif
#endif


//STN32 specific Interrupt

#ifndef TAMPER_PRIORITY
 #define TAMPER_PRIORITY  STM32_INT_PRIORITY
#endif

#ifndef RTC_PRIORITY  /*3*/
 #define RTC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef RCC_PRIORITY
 #define RCC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef EXTI_PRIORITY
 #define EXTI_PRIORITY    STM32_INT_PRIORITY
#endif
#ifndef DMAS_PRIORITY
 #define DMAS_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef ADC_PRIORITY
 #define ADC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef USB_HP_PRIORITY
 #define USB_HP_PRIORITY  STM32_INT_PRIORITY
#endif
#ifndef USB_LP_PRIORITY
 #define USB_LP_PRIORITY  STM32_INT_PRIORITY
#endif
#ifndef TIM_PRIORITY
 #define TIM_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef I2C_PRIORITY
 #define I2C_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef SPI_PRIORITY
 #define SPI_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef USART_PRIORITY
 #define USART_PRIORITY   STM32_INT_PRIORITY
#endif
#ifndef SDIO_PRIORITY
 #define SDIO_PRIORITY    STM32_INT_PRIORITY
#endif

#else  //F1/2/3/4/7 L1/4

#ifndef SYSTICK_INT_PRIORITY
 #if FREERTOS
  #define SYSTICK_INT_PRIORITY	15
  #define STM32_INT_PRIORITY	5
 #else
  #define SYSTICK_INT_PRIORITY	0	
  #define STM32_INT_PRIORITY	5
 #endif
#endif

#ifndef STM32_INT_PRIORITY
#endif
#ifndef TAMPER_PRIORITY  /*f1 2*/
#define TAMPER_PRIORITY  STM32_INT_PRIORITY
#endif
#ifndef RTC_PRIORITY  /*f1 5*/
#define RTC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef RCC_PRIORITY  /*f1 6*/
#define RCC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef EXTI_PRIORITY
#define EXTI_PRIORITY    15  //botton  use 0x0f
#endif
#ifndef DMAS_PRIORITY  /*f1 11*/
#define DMAS_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef ADC_PRIORITY  /*f1 18*/
#define ADC_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef USB_HP_PRIORITY  /*f1 19*/
#define USB_HP_PRIORITY  STM32_INT_PRIORITY
#endif
#ifndef USB_LP_PRIORITY
#define USB_LP_PRIORITY  STM32_INT_PRIORITY
#endif
#ifndef TIM_PRIORITY  /*f1 24*/
#define TIM_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef I2C_PRIORITY  /*f1 31*/
#define I2C_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef SPI_PRIORITY  /*f1 35*/
#define SPI_PRIORITY     STM32_INT_PRIORITY
#endif
#ifndef USART_PRIORITY  /*f1 37*/
#define USART_PRIORITY   STM32_INT_PRIORITY
#endif
#ifndef SDIO_PRIORITY  /*f1 49*/
#define SDIO_PRIORITY    STM32_INT_PRIORITY
#endif

#endif


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

#endif  // STM32_DEF_H
