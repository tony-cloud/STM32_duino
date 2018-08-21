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
  
  2018.1.8 change SerialUART to HardwareSerial comptatible with arduino stl libs 
           and some apps modified by huaweiwx@sina.com
  2018.7.22 Thanks csnol!  modifyed begin(baud) to begin(baud, config) parm config(optional)
           comptatible with arduino official implementation. by huaweiwx@sina.com
*/

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "stm32_def.h"
#include "stm32_gpio.h"
#include "Stream.h"
#include "util/toolschain.h"
#define BUFFER_SIZE 128

/*from Arduino_Core*/
#ifdef UART_WORDLENGTH_7B
#define SERIAL_7N1 0x04
#define SERIAL_7N2 0x0C
#define SERIAL_6E1 0x22
#define SERIAL_6E2 0x2A
#define SERIAL_6O1 0x32
#define SERIAL_6O2 0x3A
#endif

#define SERIAL_8N1 0x06
#define SERIAL_8N2 0x0E
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Stream  {
  public:
    HardwareSerial(USART_TypeDef *instance);
    void begin(const uint32_t baud, uint8_t config = SERIAL_8N1);
    void configForLowPower(void);
    void end(void);
    int available(void);
    int availableForWrite();
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(const uint8_t c);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() {
      return true;
    }; // UART always active

    void setPins(uint8_t tx, uint8_t rx);

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

  private:
    uint8_t _config;

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

#if defined(USART7) || defined(UART7)
#if (USE_SERIAL7)
extern HardwareSerial SerialUART7;
#define Serial7 SerialUART7
#endif
#endif

#if defined(USART8) || defined(UART8)
#if (USE_SERIAL8)
extern HardwareSerial SerialUART7;
#define Serial8 SerialUART8
#endif
#endif

#if defined(UART9) && (USE_SERIAL9)
extern HardwareSerial SerialUART9;
#define Serial9 SerialUART9
#endif

#if defined(UART10) && (USE_SERIAL10)
extern HardwareSerial SerialUART10;
#define Serial10 SerialUART10
#endif

#if defined(LPUART1) && (USE_LPUART1)
extern HardwareSerial SerialLPUART1;
#define LPSerial1 SerialLPUART1
#endif

#define SerialUART HardwareSerial  /*comptatible with old version*/

#endif // _HARDWARESERIAL_H_
