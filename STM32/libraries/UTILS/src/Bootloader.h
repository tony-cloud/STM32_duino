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
#include <Arduino.h>
#include "USBDevice.h"

#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_
#define USER_CODE_RAM   0x20000000U

#ifdef STM32F1  //F0/L0/F1/L1/F3
# if (FLASH_BANK1_END >  0x0801FFFFU) /*512k flash 64k ram for xC/xE*/
#  define MAX_PROG_RAM (44*1024)      /*use 0x20000000~0x2000BFFF*/
#  ifdef GD32F10X
#    define CODESEG_NUM 4
#  else
#    define CODESEG_NUM  8
#  endif
# else  /*128k flash 20k ram for x8/xB*/
#  define MAX_PROG_RAM (16*1024)      /*use 0x20000000~0x20003FFF*/
#  define  CODESEG_NUM  4
# endif
#else /*f4/7*/
# error "please add me!"
#endif

extern const uint16_t codeSegAddr[];

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

int  UTIL_checkUserCode(uint32_t usrAddr);
void UTIL_jumpToUser(uint32_t usrAddr);

#ifdef __cplusplus
 } //  extern "C"
#endif /* __cplusplus */

#endif

