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
  2018.1.8 change SerialUART to HardwareSerial comptatible with arduino stl libs and some apps huaweiwx@sina.com
*/

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "stm32_def.h"
#include "stm32_gpio.h"
#include "Stream.h"
#include "util/toolschain.h"
#define BUFFER_SIZE 128

class HardwareSerial : public Stream  {
  public:
    HardwareSerial(USART_TypeDef *instance);
    void begin(const uint32_t baud);
    void end(void);
    int available(void);
	int availableForWrite();
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(const uint8_t c);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() { return true; }; // UART always active

    void setPins(uint8_t tx,uint8_t rx);
	
    __deprecated("have a new func instead: setPins(tx,rx).add by huaweiwx")
    void stm32SetRX(uint8_t rx);

    __deprecated("have a new func instead: setPins(tx,rx).add by huaweiwx")	
    void stm32SetTX(uint8_t tx);
    
    USART_TypeDef *instance = NULL;
    UART_HandleTypeDef *handle = NULL;
    
    uint8_t receive_buffer = 0;

    uint8_t *txBuffer = NULL;
    volatile uint8_t txStart = 0;
    volatile uint8_t txEnd = 0;

    uint8_t *rxBuffer = NULL;
    volatile uint8_t rxStart = 0;
    volatile uint8_t rxEnd = 0;

//    GPIO_TypeDef *rxPort = NULL;
//    uint32_t rxPin = 0;
//    GPIO_TypeDef *txPort = NULL;
//    uint32_t txPin = 0;
	
    uint8_t rxPin = 0xff;
    uint8_t txPin = 0xff;
	
};

#if defined(USART1) && (USE_SERIAL1)
extern HardwareSerial SerialUART1;
#define Serial1 SerialUART1
#endif

#if defined(USART2) && (USE_SERIAL2)
extern HardwareSerial SerialUART2;
#define Serial2 SerialUART2
#endif

#if defined(USART3) && (USE_SERIAL3)
extern HardwareSerial SerialUART3;
#define Serial3 SerialUART3
#endif

#if defined(USART4) || defined(UART4)
#if (USE_SERIAL4)
extern HardwareSerial SerialUART4;
#define Serial4 SerialUART4
#endif
#endif

#if defined(USART5) || defined(UART5)
#if (USE_SERIAL5)
extern HardwareSerial SerialUART5;
#define Serial5 SerialUART5
#endif
#endif

#if defined(USART6) && (USE_SERIAL6)
extern HardwareSerial SerialUART6;
#define Serial6 SerialUART6
#endif

#if defined(LPUART1) && (USE_LPUART1)
extern HardwareSerial SerialLPUART1;
#define LPSerial1 SerialLPUART1
#endif

#define SerialUART HardwareSerial  /*comptatible with old version*/

#endif // _HARDWARESERIAL_H_
