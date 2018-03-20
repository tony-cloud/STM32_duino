#include "stm32_def.h"
#include <Arduino.h>
#include "syscalls.h"

//LPUART1  pins  NUCLEO_F4R5ZI at PG7/PG8
#define TXPIN PG7 
#define RXPIN PG8
extern "C" void initVariant() {
    SerialLPUART1.setPins(TXPIN,RXPIN);
//  SerialLPUART1.stm32SetTX(TXPIN);
//  SerialLPUART1.stm32SetRX(RXPIN);
}