/*
   STM32GENERIC default config file
   2018 huaweiwx@sina.com
*/

#ifndef _HAL_DEFAULT_CONFIG_H_
#define _HAL_DEFAULT_CONFIG_H_

/***************  for freeRtos ****************/
#ifndef   portUSE_HEAP
#  define portUSE_HEAP 0  /*  port heap used heap_useNewlib */
#endif

#ifndef  configTOTAL_HEAP_SIZE
# define configTOTAL_HEAP_SIZE         (RAM_LENGTH/4)
#endif

#ifndef portTickUSE_TIMx
# if defined(STM32F103RE)
    #define portTickUSE_TIMx 7
# else
    #define portTickUSE_TIMx 0   /* 0/7 use systick/TIM7*/
# endif
#else
# if (portTickUSE_TIMx !=0)||(portTickUSE_TIMx !=7)
#   error "portTickUSE_TIMx must be 0 or 7"
# endif	
#endif

#endif /* _HAL_DEFAULT_CONFIG_H_ */
