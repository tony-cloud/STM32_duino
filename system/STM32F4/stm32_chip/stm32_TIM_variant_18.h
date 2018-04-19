
const stm32_tim_pin_list_type chip_tim1 [] = {
    { TIM1  ,GPIOA, GPIO_PIN_6  ,TIM_BKIN   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_12 ,TIM_BKIN   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_9  ,TIM_CH1    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_7  ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_13 ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_8  ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_9  ,TIM_CH2    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_0  ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_14 ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_10 ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_10 ,TIM_CH3    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_1  ,TIM_CH3N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_15 ,TIM_CH3N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_11 ,TIM_CH4    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_12 ,TIM_ETR    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_7  ,TIM_ETR    , GPIO_AF1_TIM1  }, 
}; 

const stm32_tim_pin_list_type chip_tim2 [] = {
    { TIM2  ,GPIOA, GPIO_PIN_0  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_5  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_15 ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_1  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_3  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_9  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_2  ,TIM_CH3    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_10 ,TIM_CH3    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_3  ,TIM_CH4    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_2  ,TIM_CH4    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_0  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_5  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_15 ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_8  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
}; 

const stm32_tim_pin_list_type chip_tim3 [] = {
    { TIM3  ,GPIOA, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_4  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOA, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_5  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_0  ,TIM_CH3    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_1  ,TIM_CH4    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOD, GPIO_PIN_2  ,TIM_ETR    , GPIO_AF2_TIM3  }, 
}; 

const stm32_tim_pin_list_type chip_tim4 [] = {
    { TIM4  ,GPIOB, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOD, GPIO_PIN_12 ,TIM_CH1    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOD, GPIO_PIN_13 ,TIM_CH2    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF2_TIM4  }, 
}; 

const stm32_tim_pin_list_type chip_tim5 [] = {
    { TIM5  ,GPIOA, GPIO_PIN_0  ,TIM_CH1    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_1  ,TIM_CH2    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_2  ,TIM_CH3    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_3  ,TIM_CH4    , GPIO_AF2_TIM5  }, 
}; 

const stm32_tim_pin_list_type chip_tim6 [] = {
}; 

const stm32_tim_pin_list_type chip_tim7 [] = {
}; 

const stm32_tim_pin_list_type chip_tim8 [] = {
    { TIM8  ,GPIOA, GPIO_PIN_6  ,TIM_BKIN   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_5  ,TIM_CH1N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_7  ,TIM_CH1N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_0  ,TIM_CH2N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_14 ,TIM_CH2N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_1  ,TIM_CH3N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_15 ,TIM_CH3N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_0  ,TIM_ETR    , GPIO_AF3_TIM8  }, 
}; 

const stm32_tim_pin_list_type chip_tim9 [] = {
    { TIM9  ,GPIOA, GPIO_PIN_2  ,TIM_CH1    , GPIO_AF3_TIM9  }, 
    { TIM9  ,GPIOA, GPIO_PIN_3  ,TIM_CH2    , GPIO_AF3_TIM9  }, 
}; 

const stm32_tim_pin_list_type chip_tim10 [] = {
    { TIM10 ,GPIOB, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF3_TIM10 }, 
}; 

const stm32_tim_pin_list_type chip_tim11 [] = {
    { TIM11 ,GPIOB, GPIO_PIN_9  ,TIM_CH1    , GPIO_AF3_TIM11 }, 
}; 

const stm32_tim_pin_list_type chip_tim12 [] = {
    { TIM12 ,GPIOB, GPIO_PIN_14 ,TIM_CH1    , GPIO_AF9_TIM12 }, 
    { TIM12 ,GPIOB, GPIO_PIN_15 ,TIM_CH2    , GPIO_AF9_TIM12 }, 
}; 

const stm32_tim_pin_list_type chip_tim13 [] = {
    { TIM13 ,GPIOA, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF9_TIM13 }, 
}; 

const stm32_tim_pin_list_type chip_tim14 [] = {
    { TIM14 ,GPIOA, GPIO_PIN_7  ,TIM_CH1    , GPIO_AF9_TIM14 }, 
}; 

const stm32_tim_pin_list_type chip_tim15 [] = {
}; 

const stm32_tim_pin_list_type chip_tim16 [] = {
}; 

const stm32_tim_pin_list_type chip_tim17 [] = {
}; 

const stm32_tim_pin_list_type chip_tim18 [] = {
}; 

const stm32_tim_pin_list_type chip_tim [] = {
    { TIM1  ,GPIOA, GPIO_PIN_6  ,TIM_BKIN   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_12 ,TIM_BKIN   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_9  ,TIM_CH1    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_7  ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_13 ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_8  ,TIM_CH1N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_9  ,TIM_CH2    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_0  ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_14 ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_10 ,TIM_CH2N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_10 ,TIM_CH3    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_1  ,TIM_CH3N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOB, GPIO_PIN_15 ,TIM_CH3N   , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_11 ,TIM_CH4    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOA, GPIO_PIN_12 ,TIM_ETR    , GPIO_AF1_TIM1  }, 
    { TIM1  ,GPIOE, GPIO_PIN_7  ,TIM_ETR    , GPIO_AF1_TIM1  }, 
    { TIM2  ,GPIOA, GPIO_PIN_0  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_5  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_15 ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_1  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_3  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_9  ,TIM_CH2    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_2  ,TIM_CH3    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_10 ,TIM_CH3    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_3  ,TIM_CH4    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_2  ,TIM_CH4    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_0  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_5  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOA, GPIO_PIN_15 ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM2  ,GPIOB, GPIO_PIN_8  ,TIM_ETR    , GPIO_AF1_TIM2  }, 
    { TIM3  ,GPIOA, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_4  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOA, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_5  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_0  ,TIM_CH3    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOB, GPIO_PIN_1  ,TIM_CH4    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOC, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF2_TIM3  }, 
    { TIM3  ,GPIOD, GPIO_PIN_2  ,TIM_ETR    , GPIO_AF2_TIM3  }, 
    { TIM4  ,GPIOB, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOD, GPIO_PIN_12 ,TIM_CH1    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOD, GPIO_PIN_13 ,TIM_CH2    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF2_TIM4  }, 
    { TIM4  ,GPIOB, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF2_TIM4  }, 
    { TIM5  ,GPIOA, GPIO_PIN_0  ,TIM_CH1    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_1  ,TIM_CH2    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_2  ,TIM_CH3    , GPIO_AF2_TIM5  }, 
    { TIM5  ,GPIOA, GPIO_PIN_3  ,TIM_CH4    , GPIO_AF2_TIM5  }, 
    { TIM8  ,GPIOA, GPIO_PIN_6  ,TIM_BKIN   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_5  ,TIM_CH1N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_7  ,TIM_CH1N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_7  ,TIM_CH2    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_0  ,TIM_CH2N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_14 ,TIM_CH2N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_8  ,TIM_CH3    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_1  ,TIM_CH3N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOB, GPIO_PIN_15 ,TIM_CH3N   , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOC, GPIO_PIN_9  ,TIM_CH4    , GPIO_AF3_TIM8  }, 
    { TIM8  ,GPIOA, GPIO_PIN_0  ,TIM_ETR    , GPIO_AF3_TIM8  }, 
    { TIM9  ,GPIOA, GPIO_PIN_2  ,TIM_CH1    , GPIO_AF3_TIM9  }, 
    { TIM9  ,GPIOA, GPIO_PIN_3  ,TIM_CH2    , GPIO_AF3_TIM9  }, 
    { TIM10 ,GPIOB, GPIO_PIN_8  ,TIM_CH1    , GPIO_AF3_TIM10 }, 
    { TIM11 ,GPIOB, GPIO_PIN_9  ,TIM_CH1    , GPIO_AF3_TIM11 }, 
    { TIM12 ,GPIOB, GPIO_PIN_14 ,TIM_CH1    , GPIO_AF9_TIM12 }, 
    { TIM12 ,GPIOB, GPIO_PIN_15 ,TIM_CH2    , GPIO_AF9_TIM12 }, 
    { TIM13 ,GPIOA, GPIO_PIN_6  ,TIM_CH1    , GPIO_AF9_TIM13 }, 
    { TIM14 ,GPIOA, GPIO_PIN_7  ,TIM_CH1    , GPIO_AF9_TIM14 }, 
}; 
