/*
  Copyright (c) 2017 Daniel Fekete

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
#include "Arduino.h"
#include <reent.h>        // required for _write_r
#include "stm32_debug.h"
//#include "stm32def.h"
//#include "STM32System.h"

//#include "cmsis_gcc.h"

#if  __CORTEX_M  == 0  /* M0/M0+ not swo */
#if USE_SWOPRINTERR > 0
#error "!This is a cortex M0 chip, unsupport SWO!"
#endif
#endif

static const int print_fileno = 3;

static Print *print;
static Stream *stdprint = &Serial;  //default serial outport

#if USE_SWOPRINTERR < 1
static Stream *errprint = &Serial;  //default serial outport
#endif

int stm32SetPrintOutput(Print *p) {
    if (p == NULL) {
        print = NULL;
        return 0;
    }

    if (isInterrupt() && print != NULL) {
        return 0;
    }

    while(print != NULL);
    print = p;

    return print_fileno;
}

void setStdPrintDev(Stream *p,int file) {
	if (file == STDOUT_FILENO){
        stdprint = p;
	}
#if USE_SWOPRINTERR < 1
	else if (file == STDERR_FILENO) {
        errprint = p;
	} 
#endif
}

extern "C" int _write(int file, char *ptr, int len ) {
	if (file == STDOUT_FILENO){
		return stdprint->write(ptr, len);
	}
	if (file == STDERR_FILENO) {
#if USE_SWOPRINTERR < 1
		errprint->write(ptr, len);
		errprint->flush();
#else
	int cnt = len;
	    while(cnt){
	   	   ITM_SendChar(*ptr);
		   ptr++;
           cnt--;		   
		}
#endif
		return len;
	} 
	if (file == print_fileno) {
		if (print != NULL)  return print->write(ptr, len);
	}
	
	// TODO show error
	return 0;  //return no-void warning add by huaweiwx@sina.com 2017.7.21
}

struct _reent;
extern "C"  int _write_r(struct _reent *r, int file, const void *ptr, size_t len) {
  (void) r;     /* Not used, avoid warning */
  _write(file, (char *)ptr, (int)len);
  return len;
}

#if  __CORTEX_M  > 0  /* M0/M0+ not swo */
  SWO  SerialSWO;
#endif