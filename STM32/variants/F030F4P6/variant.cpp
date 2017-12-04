#include "stm32_build_defines.h"
#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

#define TXPIN PA9  
#define RXPIN PA10
extern "C" void initVariant() {
    //UART1 is PA9/PA10 pins  f030f4p6 default PA2/PA3 must remaped huaweiwx@sina.com
    SerialUART1.setPins(TXPIN,RXPIN);
//    SerialUART1.stm32SetTX(PA9);
//    SerialUART1.stm32SetRX(PA10);
}