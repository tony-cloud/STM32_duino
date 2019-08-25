#ifndef STM32_SYSTEM_H
#define STM32_SYSTEM_H

#include "Arduino.h"
#include "unistd.h"

// Returns if we are in an interrupt
inline bool isInterrupt() {
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0 ;
}

#ifdef __cplusplus

// Internal: what will be the
int stm32SetPrintOutput(Print *p);
void setStdPrintDev(Stream *p, int file);

#endif

#endif

