/*
   STM32GENERIC default config file
   2018 huaweiwx@sina.com
*/

#ifndef _HAL_DEFAULT_CONFIG_H_
#define _HAL_DEFAULT_CONFIG_H_

/***************  for freeRtos ****************/

#ifndef portTickUSE_TIMx
    #define portTickUSE_TIMx 0   /* 0/6/17 use systick/TIM6/TIM17*/
#else
# if (portTickUSE_TIMx !=0)||(portTickUSE_TIMx !=6)||(portTickUSE_TIMx !=17)
#   error "portTickUSE_TIMx must be 0/6 or 7"
# endif	
#endif


#endif /* _HAL_DEFAULT_CONFIG_H_ */
