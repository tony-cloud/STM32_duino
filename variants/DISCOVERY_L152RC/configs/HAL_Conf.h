/*
   STM32GENERIC default config file
   2018 huaweiwx@sina.com
*/

#ifndef _HAL_DEFAULT_CONFIG_H_
#define _HAL_DEFAULT_CONFIG_H_

/***************  for freeRtos ****************/

#ifndef portTickUSE_TIMx
  #define portTickUSE_TIMx 7   /* 0/7 use systick/TIM7*/
#else
# if (portTickUSE_TIMx !=0)||(portTickUSE_TIMx !=7)
#   error "portTickUSE_TIMx must be 0 or 7"
# endif	
#endif

#endif /* _HAL_DEFAULT_CONFIG_H_ */
