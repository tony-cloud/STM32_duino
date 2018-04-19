#include "stm32_def.h"

#if (USER_USBDCONF < 1)
	
#ifdef STM32F1
 #include "usbd_conf_F1.inc"
#elif defined(STM32F2)
// #include "usbd_conf_F2.inc"
#elif defined(STM32F3)
 #include "usbd_conf_F3.inc"
#elif defined(STM32F4)
 #include "usbd_conf_F4.inc"
#elif defined(STM32F7)
 #include "usbd_conf_F7.inc"
#elif defined(STM32L0)
 #include "usbd_conf_L0.inc"
#elif defined(STM32L1)
 #include "usbd_conf_L1.inc"
#elif defined(STM32F2)
#elif defined(STM32L4)
 #include "usbd_conf_L4.inc"
#endif

#endif
