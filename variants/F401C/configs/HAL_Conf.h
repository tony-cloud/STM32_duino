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
    #define portTickUSE_TIMx 0   /* 0/11 use systick/TIM11*/
#else
# if (portTickUSE_TIMx !=0)||(portTickUSE_TIMx !=11)
#   error "portTickUSE_TIMx must be 0 or 11"
# endif	
#endif


#endif /* _HAL_DEFAULT_CONFIG_H_ */
