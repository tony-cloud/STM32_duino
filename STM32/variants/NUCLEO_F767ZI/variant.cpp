#include "stm32_build_defines.h"
#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

extern "C" void initVariant() {
    //UART3  pins  NUCLEO_F746ZI undefaulted, linked at PD8/PD9
    SerialUART3.stm32SetTX(PD8);
    SerialUART3.stm32SetRX(PD9);
}