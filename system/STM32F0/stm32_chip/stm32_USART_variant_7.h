
const stm32_af_pin_list_type chip_af_usart_rx [] = {
//USART1
    { USART1, GPIOA, GPIO_PIN_10 , GPIO_AF1_USART1}, 
//USART2
    { USART2, GPIOA, GPIO_PIN_3  , GPIO_AF1_USART2}, 
}; 

const stm32_af_pin_list_type chip_af_usart_tx [] = {
//USART1
    { USART1, GPIOA, GPIO_PIN_9  , GPIO_AF1_USART1}, 
//USART2
    { USART2, GPIOA, GPIO_PIN_2  , GPIO_AF1_USART2}, 
    { USART2, GPIOA, GPIO_PIN_14 , GPIO_AF1_USART2}, 
}; 
