/*
  Copyright (c) 2017 huawei

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include "Bootloader.h"

#if defined(STM32F1)  //F0/L0/F1/L1/F3
#  if (FLASH_BANK1_END >  0x0801FFFFU) /*512k flash 64k ram for xC/xE*/
#    ifdef GD32F10X
        const  uint16_t codeSegAddr[] = {64,2*64,3*64,};
#    else
        const  uint16_t codeSegAddr[] = {64, (uint8_t)2*64,(uint8_t)3*64,(uint8_t)4*64,(uint8_t)5*64,(uint8_t)6*64,(uint8_t)7*64,};
#    endif
#  else  /*128k flash 20k ram for x8/xB*/
        const uint16_t codeSegAddr[] = { 16,3*16,5*16,};
#  endif
#else /*f4/7*/
# error "please add me!"
#endif


extern "C" int UTIL_checkUserCode(uint32_t usrAddr) {
    uint32_t sp = *(volatile uint32_t *) usrAddr;

    if ((sp & 0x2FFE0000) == 0x20000000) {
        return (1);
    } else {
        return (0);
    }
}

extern "C" void UTIL_jumpToUser(uint32_t usrAddr) {
  // Dedicated function with no call to any function (appart the last call)
  // This way, there is no manipulation of the stack here, ensuring that GGC
  // didn't insert any pop from the SP after having set the MSP.
  typedef void (*funcPtr)(void);

  uint32_t jumpAddr = *(volatile uint32_t *)(usrAddr + 0x04); /* reset ptr in vector table */

  funcPtr usrMain = (funcPtr) jumpAddr;

  asm volatile("msr msp, %0"::"g"
               (*(volatile uint32_t *)usrAddr));
  *(uint32_t *) 0xE000ED08 = usrAddr;   /* 设置中断向量表地址 */
  usrMain();                            /* go! */
}

#ifdef CHK_JUMP_TO_SRAM    /*only for develop ram debug*/
//reset boot to ram if available
# include "ram_boot.h"

#endif