#include "stm32_build_defines.h"

#ifdef STM32F0
    #include "stm32f0xx_ll_gpio.h"
#endif
#ifdef STM32F1
    #include "stm32f1xx_ll_gpio.h"
#endif
#ifdef STM32F2
    #include "stm32f2xx_ll_gpio.h"
#endif
#ifdef STM32F3
    #include "stm32f3xx_ll_gpio.h"
#endif
#ifdef STM32F4
    #include "stm32f4xx_ll_gpio.h"
#endif
#ifdef STM32F7
    #include "stm32f7xx_ll_gpio.h"
#endif

#ifdef STM32H7
# define LL_GPIO_SetOutputPin(p,m)   (p)->BSRRH=(m)
# define LL_GPIO_ResetOutputPin(p,m) (p)->BSRRL=(m)
# define LL_GPIO_IsInputPinSet(p,m)  (((p)->IDR & m)?1:0)
# define LL_GPIO_TogglePin(p,m)      (p)->ODR ^= (m)
//    #include "stm32h7xx_ll_gpio.h"   
#endif
#ifdef STM32L0
    #include "stm32l0xx_ll_gpio.h"
#endif
#ifdef STM32L1
    #include "stm32l1xx_ll_gpio.h"
#endif
#ifdef STM32L4
    #include "stm32l4xx_ll_gpio.h"
#endif
