#include "stm32_build_defines.h"
#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

extern "C" void initVariant() {
    //UART3 is connected to ST-Link V2.1 as Virtual Com port on non-default PD9/PD8 pins
    SerialUART3.stm32SetTX(PD8);
    SerialUART3.stm32SetRX(PD9);
}