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
#include "stm32_debug.h"

#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunused-parameter"

//------------------------------------------------------------------------------
/** calibration factor for delayMS */
#if defined(STM32F7)||defined(STM32H7)
# define CAL_FACTOR (F_CPU/2000)
#else
# define CAL_FACTOR (F_CPU/7000)
#endif

#if  __CORTEX_M  > 0  /* M0/M0+ not swo */
#  if USE_ITMRXBUFFER > 0
     volatile int32_t ITM_RxBuffer;                    /*!< External variable to receive characters. */
#  endif
#endif 
/** delay between led error flashes
 * \param[in] millis milliseconds to delay
 */
static void delayMS(uint32_t millis) {
  uint32_t iterations = millis * CAL_FACTOR;
  uint32_t i;
  for(i = 0; i < iterations; ++i) {
    asm volatile("nop\n\t");
  }
}

static void nblink(int n, int l){
  if(l){	
	for  (uint8_t i = 0; i < 2*n; i++) {
      digitalToggle(LED_BUILTIN);
      delayMS(250);
    }
  }else{
    for (uint8_t i = 0; i < n; i++) {
      digitalToggle(LED_BUILTIN);
      delayMS(10);
      digitalToggle(LED_BUILTIN);
      delayMS(240);
    }
  }
}

void errorLedBlink(char* file, uint32_t n) {
  UNUSED(file);	
  noInterrupts();
  pinMode(LED_BUILTIN, OUTPUT);
#if (LED_BUILTIN_MASK & 0x01)
  digitalWrite(LED_BUILTIN,LOW);
#else
  digitalWrite(LED_BUILTIN,HIGH);
#endif

  int t = n / 1000;
  int h = n % 1000;
  int d = h % 100;
  int l = n % 10;

  h /= 100;
  d /= 10;

  if(l == 0) l = 10;
  
  for (;;) {
	nblink(t,1);	  
	nblink(h,0);
	nblink(d,1);
    nblink(l,0);
	delayMS(2000);
  }
}

//debug_if add by huaweiwx@sina.com  2017.12.8
void debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void printErrFileLine(char* file, uint32_t n) {
  debug("\r\nErr! File:'%s' on Line:%d",file,n);
}

#if USE_ERRORBLINK >0
void errorCallback(char* file, uint32_t n) __attribute__ ((weak, alias("errorLedBlink")));
#else
void errorCallback(char* file, uint32_t n) __attribute__ ((weak, alias("printErrFileLine")));
#endif

//debug_if add by huaweiwx@sina.com  2017.12.8
void debug_if(int condition, const char *format, ...) {	
    if (condition) {
       va_list args;
       va_start(args, format);
       vfprintf(stderr, format, args);
       va_end(args);
    }
}

void print_log(const char *level, const char *format, const char *file, const int line, ...) {

    uint32_t m = micros();

    uint32_t seconds = m / 1000000;
    uint32_t fractions = m % 1000000;

    debug("[%2u.%-6u]%10s %3d %s:", seconds, fractions, file, line, level);

    va_list argList;
    va_start(argList, line);
    vfprintf(stderr, format, argList);
    va_end(argList);
}

char *stm32PortPinName(GPIO_TypeDef *port, uint32_t pinMask) {
    for(size_t i=0; i<sizeof(variant_pin_list) / sizeof(variant_pin_list[0]); i++) {
        if (variant_pin_list[i].port == port && variant_pin_list[i].pinMask == pinMask) {
            return stm32PinName(i);
        }
    }
//    return (char*)"Unknown pin";
    return NULL;
}

char *stm32PinName(uint8_t pin) {
    if (pin >= NUM_DIGITAL_PINS) {
        return NULL;
    }
    static char ret[10];
    int index = 0;

    if (variant_pin_list[0].port != GPIOA || variant_pin_list[0].pinMask != GPIO_PIN_0) {
        if (pin < 10) {
            ret[index++] = '0' + pin;
        } else {
            ret[index++] = '0' + pin / 10;
            ret[index++] = '0' + pin % 10;
        }
        ret[index++] = ' ';
        ret[index++] = '(';
    }

    ret[index++] = 'P';

    stm32_port_pin_type port_pin = variant_pin_list[pin];

    ret[index++] = 'A' + ((uint32_t)port_pin.port - (uint32_t)GPIOA) / ((uint32_t)GPIOB - (uint32_t)GPIOA);
    int num = __builtin_ffs(port_pin.pinMask) - 1;
    if (num < 10) {
        ret[index++] = '0' + num;
    } else {
        ret[index++] = '0' + num / 10;
        ret[index++] = '0' + num % 10;
    }

    if (variant_pin_list[0].port != GPIOA || variant_pin_list[0].pinMask != GPIO_PIN_0) {
        ret[index++] = ')';
    }

    ret[index] = 0;

    return ret;

}

//_Error_Handler() created by CubeMX. huaweiwx@sina.com  2017.12.8
void _Error_Handler(char* file, uint32_t line) __weak;
void _Error_Handler(char* file, uint32_t line){
    errorCallback(file,line);
	while(1)
		yield();
}

#if USE_HARDFAUILTHOOK
void ProcessHardFault(uint32_t lr, uint32_t msp, uint32_t psp)
{
    uint32_t exception_num;
    uint32_t r0, r1, r2, r3, r12, pc, psr;
    uint32_t *stack;

    stack = (uint32_t *)msp;

    /* Get information from stack */
    r0  = stack[0];
    r1  = stack[1];
    r2  = stack[2];
    r3  = stack[3];
    r12 = stack[4];
    lr  = stack[5];
    pc  = stack[6];
    psr = stack[7];

    /* Check T bit of psr */
    if((psr & (1 << 24)) == 0)
    {
        debug("PSR T bit is 0.\nHard fault caused by changing to ARM mode!\n");
         while(1);
    }

    /* Check hard fault caused by ISR */
    exception_num = psr & xPSR_ISR_Msk;
    if(exception_num > 0)
    {
        /*
        Exception number
            0 = Thread mode
            1 = Reserved
            2 = NMI
            3 = HardFault
            4-10 = Reserved11 = SVCall
            12, 13 = Reserved
            14 = PendSV
            15 = SysTick, if implemented[a]
            16 = IRQ0.
                .
                .
            n+15 = IRQ(n-1)[b]
            (n+16) to 63 = Reserved.
        The number of interrupts, n, is 32
        */

        debug("Hard fault is caused in IRQ #%d\n", exception_num - 16);
      while(1);
    }

    debug("Hard fault location is at 0x%08x\n", pc);
    /*
        If the hard fault location is a memory access instruction, You may debug the load/store issues.

        Memory access faults can be caused by:
            Invalid address - read/write wrong address
            Data alignment issue - Violate alignment rule of Cortex-M processor
            Memory access permission - MPU violations or unprivileged access (Cortex-M0+)
            Bus components or peripheral returned an error response.
    */
    debug("r0  = 0x%x\n", r0);
    debug("r1  = 0x%x\n", r1);
    debug("r2  = 0x%x\n", r2);
    debug("r3  = 0x%x\n", r3);
    debug("r12 = 0x%x\n", r12);
    debug("lr  = 0x%x\n", lr);
    debug("pc  = 0x%x\n", pc);
    debug("psr = 0x%x\n", psr);
    while(1);
}

void hard_fault_handler_hook(uint32_t lr, uint32_t msp, uint32_t psp) __attribute__ ((weak, alias("ProcessHardFault")));

#endif

#ifdef USE_FULL_ASSERT
//assert_failed() used by stm32_hal. huaweiwx@sina.com  2017.12.8
void assert_failed(uint8_t* file, uint32_t line) __weak;
void assert_failed(uint8_t* file, uint32_t line)
{
    errorCallback((char*)file,line);
	while(1)
		yield();
};

 /**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  #if USE_HARDFAUILTHOOK
    __asm volatile(
    " tst lr, #4   \n" 
    " ite eq       \n" 
    " mrseq r0,msp \n"
    " mrsne r0,psp \n"
    " b hard_fault_handler_hook \n"
    );
  #else
  	errorCallback((char*)"HardFault",31);
  #endif
    while(1);
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
	errorCallback("MemFault",32);
    while(1);
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
	errorCallback("BusFault",33);
    while(1);
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
	errorCallback("UsageFault",34);
    while(1);
}
#endif
