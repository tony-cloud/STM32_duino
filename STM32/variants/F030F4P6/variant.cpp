#include "stm32_build_defines.h"
#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

extern "C" void initVariant() {
    //UART1 is PA9/PA10 pins  f030f4p6 default PA2/PA3 must remaped huaweiwx@sina.com
    SerialUART1.stm32SetTX(PA9);
    SerialUART1.stm32SetRX(PA10);
}