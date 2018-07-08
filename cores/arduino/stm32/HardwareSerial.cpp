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
  
  2018.1.8 change SerialUART to HardwareSerial, comptatible with arduino stl libs and some apps huaweiwx@sina.com
*/

/**
 * TODO: Check if txBuffer is NULL in every method
 * TODO: generate different BUFFER_SIZE values for different boards based on available memory
 * TODO: add alternate pin selection functions
 * TODO: add constructor with custom buffer parameter
 */
#include "HardwareSerial.h"
#include "stm32_gpio_af.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
/**
 * Set the underlying UART instance.
 */
HardwareSerial::HardwareSerial(USART_TypeDef *instance) {
    this->instance = instance;
}

/**
 * Arduino always instantiates the Serial object.
 *
 * To save memory, this implementation will:
 * - not use any memory if begin() is never called
 * - use statically allocated memory, if begin() is called exactly in one HardwareSerials.
 * - use statically allocated memory for the first, and malloc() for any subsequent calls to begin() on DIFFERENT HardwareSerials.
 */

void HardwareSerial::begin(const uint32_t baud) {
  if (txBuffer == NULL) {
	static uint8_t tx[BUFFER_SIZE];
	static uint8_t static_tx_used = 0;

	if (!static_tx_used) {
	  txBuffer = (uint8_t*)tx;
		static_tx_used = true;
	} else {
	  txBuffer = (uint8_t*)malloc(BUFFER_SIZE);
	}
  }

  if (rxBuffer == NULL) {
  	static uint8_t rx[BUFFER_SIZE];
  	static uint8_t static_rx_used = 0;

  	if (!static_rx_used) {
  	  rxBuffer = (uint8_t*)rx;
  		static_rx_used = true;
  	} else {
  	  rxBuffer = (uint8_t*)malloc(BUFFER_SIZE);
  	}
  }

  if (handle == NULL) {
  	static UART_HandleTypeDef h = {};
  	static uint8_t static_handle_used = 0;

  	if (!static_handle_used) {
  		handle = &h;
  	static_handle_used = true;
  	} else {
  		handle = (UART_HandleTypeDef*)malloc(sizeof(UART_HandleTypeDef));
  	}
  }

  handle->Instance = instance;
  
#if defined(USART1) && (USE_SERIAL1)
  if (handle->Instance == USART1) {
    __HAL_RCC_USART1_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART1_IRQn, USART_PRIORITY, 0); //define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART1_IRQn); 
  }
#endif
  
#if defined(USART2) && (USE_SERIAL2)
  if (handle->Instance == USART2) {
    __HAL_RCC_USART2_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART2_IRQn, USART_PRIORITY, 0); //define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART2_IRQn); 
  }
#endif
  
#if defined(USART3) && (USE_SERIAL3)
  if (handle->Instance == USART3) {
    __HAL_RCC_USART3_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART3_IRQn, USART_PRIORITY, 0); //define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART3_IRQn); 
  }
#endif
  
#if defined(UART4) && (USE_SERIAL4)
  if (handle->Instance == UART4) {
    __HAL_RCC_UART4_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART4_IRQn, USART_PRIORITY, 0);//define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  }
#endif
#if defined(USART4) && (USE_SERIAL4)
  if (handle->Instance == USART4) {
    __HAL_RCC_USART4_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART4_IRQn, USART_PRIORITY, 0); //define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART4_IRQn); 
  }
#endif
  
#if defined(UART5) && (USE_SERIAL5)
  if (handle->Instance == UART5) {
    __HAL_RCC_UART5_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART5_IRQn, USART_PRIORITY, 0);//define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(UART5_IRQn);
  }
#endif
#if defined(USART5) && (USE_SERIAL5)
  if (handle->Instance == USART5) {
    __HAL_RCC_USART5_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART5_IRQn, USART_PRIORITY, 0);//define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART5_IRQn);
  }
#endif

#if defined(USART6) && (USE_SERIAL6)
  if (handle->Instance == USART6) {
    __HAL_RCC_USART6_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART6_IRQn, USART_PRIORITY, 0);//define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  }
#endif

#if defined(LPUART1) && (USE_LPUART1)
  if (handle->Instance == LPUART1) {
    __HAL_RCC_LPUART1_CLK_ENABLE();
    HAL_NVIC_SetPriority(LPUART1_IRQn, USART_PRIORITY, 0);//define in stm32_def.h huaweiwx@sina.com 2017.12
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
	
    if((txPin < 0xff) && (rxPin <0xff))
       stm32AfLPUARTInit(instance, 
                  variant_pin_list[rxPin].port,
				  variant_pin_list[rxPin].pinMask,
                  variant_pin_list[txPin].port,
				  variant_pin_list[txPin].pinMask);
    else			  
       stm32AfLPUARTInit(instance, NULL,0,NULL,0);

   }
   else
	if((txPin < 0xff) && (rxPin <0xff))
		stm32AfUARTInit(instance, 
					variant_pin_list[rxPin].port,
					variant_pin_list[rxPin].pinMask,
					variant_pin_list[txPin].port,
					variant_pin_list[txPin].pinMask);
	else			  
		stm32AfUARTInit(instance, NULL,0,NULL,0);	   
 
#else
  if((txPin < 0xff) && (rxPin <0xff))
    stm32AfUARTInit(instance, 
                  variant_pin_list[rxPin].port,
				  variant_pin_list[rxPin].pinMask,
                  variant_pin_list[txPin].port,
				  variant_pin_list[txPin].pinMask);
  else			  
    stm32AfUARTInit(instance, NULL,0,NULL,0);
#endif
 
  handle->Init.BaudRate = baud; 
  handle->Init.WordLength = UART_WORDLENGTH_8B;
  handle->Init.StopBits = UART_STOPBITS_1; 
  handle->Init.Parity = UART_PARITY_NONE; 
  handle->Init.Mode = UART_MODE_TX_RX; 
  handle->Init.HwFlowCtl = UART_HWCONTROL_NONE; 
  
#if defined(LPUART1) && (USE_LPUART1) && defined(STM32L4)
  if (handle->Instance == LPUART1) {
    handle->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    handle->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#if defined(USART_PRESC_PRESCALER)  /* L4R5/7 */
    handle->Init.ClockPrescaler = UART_PRESCALER_DIV1;
    handle->FifoMode = UART_FIFOMODE_DISABLE;
#endif	
  }	
  HAL_UART_Init(handle);
#if defined(USART_CR1_FIFOEN) /* L4R5/7 */
  HAL_UARTEx_SetTxFifoThreshold(handle, UART_TXFIFO_THRESHOLD_1_8);
  HAL_UARTEx_SetRxFifoThreshold(handle, UART_RXFIFO_THRESHOLD_1_8);
#endif

#else  
  handle->Init.OverSampling = UART_OVERSAMPLING_16; 
  HAL_UART_Init(handle);
#endif

  HAL_UART_Receive_IT(handle, &receive_buffer, 1);
    
}

void HardwareSerial::end(void) {
#if defined(USART1) && (USE_SERIAL1)
  if (handle->Instance == USART1) {
    HAL_NVIC_DisableIRQ(USART1_IRQn);
//    __HAL_RCC_USART1_CLK_DISABLE();
  }
#endif
  
#if defined(USART2) && (USE_SERIAL2)
  if (handle->Instance == USART2) {
    HAL_NVIC_DisableIRQ(USART2_IRQn); 
    __HAL_RCC_USART2_CLK_DISABLE();
  }
#endif
  
#if defined(USART3) && (USE_SERIAL3)
  if (handle->Instance == USART3) {
    HAL_NVIC_DisableIRQ(USART3_IRQn); 
    __HAL_RCC_USART3_CLK_DISABLE();
  }
#endif
  
#if defined(UART4) && (USE_SERIAL4)
  if (handle->Instance == UART4) {
    HAL_NVIC_DisableIRQ(UART4_IRQn);
    __HAL_RCC_UART4_CLK_DISABLE();
  }
#endif
#if defined(USART4) && (USE_SERIAL4)
  if (handle->Instance == USART4) {
    HAL_NVIC_DisableIRQ(USART4_IRQn); 
    __HAL_RCC_USART4_CLK_DISABLE();
  }
#endif
  
#if defined(UART5) && (USE_SERIAL5)
  if (handle->Instance == UART5) {
    HAL_NVIC_DisableIRQ(UART5_IRQn);
    __HAL_RCC_UART5_CLK_DISABLE();
  }
#endif
#if defined(USART5) && (USE_SERIAL5)
  if (handle->Instance == USART5) {
    HAL_NVIC_DisableIRQ(USART5_IRQn);
    __HAL_RCC_USART5_CLK_DISABLE();
  }
#endif

#if defined(USART6) && (USE_SERIAL6)
  if (handle->Instance == USART6) {
    HAL_NVIC_DisableIRQ(USART6_IRQn);
    __HAL_RCC_USART6_CLK_DISABLE();
  }
#endif

#if defined(LPUART1) && (USE_LPUART1)
  if (handle->Instance == LPUART1) {
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);
    __HAL_RCC_LPUART1_CLK_DISABLE();
  }
#endif   
}

int HardwareSerial::available() {
  if (rxEnd >= rxStart) return (rxEnd - rxStart);
  return BUFFER_SIZE + rxEnd - rxStart;
}

int HardwareSerial::availableForWrite() {  
    return txEnd != txStart;  
}  

int HardwareSerial::peek() {
    if (available()) {
    return rxBuffer[rxStart % BUFFER_SIZE];
  } else {
    return -1;
  }
}

void HardwareSerial::flush() {
    
    while(txEnd % BUFFER_SIZE != txStart % BUFFER_SIZE);
}

int HardwareSerial::read() {
  if (available()) {
    return rxBuffer[rxStart++ % BUFFER_SIZE];
  } else {
    return -1;
  }
}

size_t HardwareSerial::write(const uint8_t c) {
  while((txEnd + 1) % BUFFER_SIZE == txStart % BUFFER_SIZE);
  
  txBuffer[txEnd % BUFFER_SIZE] = c;
  txEnd++;
  if (txEnd % BUFFER_SIZE == (txStart + 1) % BUFFER_SIZE) {
    HAL_UART_Transmit_IT(handle, &txBuffer[txStart % BUFFER_SIZE], 1);
  }
  return 1;
}

void HardwareSerial::stm32SetRX(uint8_t rx) {
    rxPin = rx;
}

void HardwareSerial::stm32SetTX(uint8_t tx) {
    txPin = tx;
}

void HardwareSerial::setPins(uint8_t tx,uint8_t rx) {
    txPin = tx;
    rxPin = rx;
}
//// Interrupt

HardwareSerial *interruptUART;

#ifdef USART1
#if (USE_SERIAL1)
extern "C" void USART1_IRQHandler(void) {
  interruptUART = &SerialUART1;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART1(USART1);
#endif
#endif

#ifdef USART2
#if (USE_SERIAL2)
extern "C" void USART2_IRQHandler(void) {
  interruptUART = &SerialUART2;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART2(USART2);
#endif
#endif

#ifdef USART3
#if (USE_SERIAL3)
extern "C" void USART3_IRQHandler(void) {
  interruptUART = &SerialUART3;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART3(USART3);
#endif
#endif

#ifdef UART4
#if (USE_SERIAL4)
extern "C" void UART4_IRQHandler(void) {
  interruptUART = &SerialUART4;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART4(UART4);
#endif
#endif
#ifdef USART4
#if (USE_SERIAL4)
extern "C" void USART4_IRQHandler(void) {
  interruptUART = &SerialUART4;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART4(USART4);
#endif
#endif

#ifdef UART5
#if (USE_SERIAL5)
extern "C" void UART5_IRQHandler(void) {
  interruptUART = &SerialUART5;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART5(UART5);
#endif
#endif
#ifdef USART5
#if (USE_SERIAL5)
extern "C" void USART5_IRQHandler(void) {
  interruptUART = &SerialUART5;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART5(USART5);
#endif
#endif

#ifdef USART6
#if (USE_SERIAL6)
extern "C" void USART6_IRQHandler(void) {
  interruptUART = &SerialUART6;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialUART6(USART6);
#endif
#endif

#ifdef LPUART1
#if (USE_LPUART1)
extern "C" void LPUART1_IRQHandler(void) {
  interruptUART = &SerialLPUART1;
  HAL_UART_IRQHandler(interruptUART->handle);
}
HardwareSerial SerialLPUART1(LPUART1);
#endif
#endif

extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  interruptUART->txStart++;
  if (interruptUART->txStart != interruptUART->txEnd) {
    HAL_UART_Transmit_IT(interruptUART->handle, &interruptUART->txBuffer[interruptUART->txStart % BUFFER_SIZE], 1);
  }
}


extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  interruptUART->rxBuffer[interruptUART->rxEnd % BUFFER_SIZE] = interruptUART->receive_buffer;
  interruptUART->rxEnd++;
  HAL_UART_Receive_IT(interruptUART->handle, &interruptUART->receive_buffer, 1);
}

