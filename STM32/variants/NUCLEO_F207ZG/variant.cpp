#include "stm32_build_defines.h"
#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

#define RXPIN PD9
#define TXPIN PD8 
extern "C" void initVariant() {
    //UART3 is connected to ST-Link V2.1 as Virtual Com port on non-default PD9/PD8 pins
    SerialUART3.setPins(RXPIN,TXPIN);
}