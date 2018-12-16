#include "stm32_build_defines.h"


#ifdef  CUSTOM_SYSTEM_C
#  include CUSTOM_SYSTEM_C
#  pragma message "used custom CMSIS system file"
#else
#  if defined(UNUSED_CMSIS_SYSTEM)&& (UNUSED_CMSIS_SYSTEM > 0)  /* has .c or .S file auto select in project or variant path */
#     pragma message "unused CMSIS system file"
#  else		
	#ifdef STM32F0
		#include "system_stm32f0xx.c"
	#endif
	#ifdef STM32F1
		#include "system_stm32f1xx.c"
	#endif
	#ifdef STM32F2
		#include "system_stm32f2xx.c"
	#endif
	#ifdef STM32F3
		#include "system_stm32f3xx.c"
	#endif
	#ifdef STM32F4
		#include "system_stm32f4xx.c"
	#endif
	#ifdef STM32F7
		#include "system_stm32f7xx.c"
	#endif
	#ifdef STM32H7
		#include "system_stm32h7xx.c"
	#endif
	#ifdef STM32L0
		#include "system_stm32l0xx.c"
	#endif
	#ifdef STM32L1
		#include "system_stm32l1xx.c"
	#endif
	#ifdef STM32L4
		#include "system_stm32l4xx.c"
	#endif	
#  endif
#endif
