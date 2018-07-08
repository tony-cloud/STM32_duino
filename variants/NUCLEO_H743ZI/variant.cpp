#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

#define TXPIN PD8 
#define RXPIN PD9
extern "C" void initVariant() {
    //UART3  pins  NUCLEO_H743ZI undefaulted, linked at PD8/PD9
    SerialUART3.setPins(TXPIN,RXPIN);
//    SerialUART3.stm32SetTX(PD8);
//    SerialUART3.stm32SetRX(PD9);
}