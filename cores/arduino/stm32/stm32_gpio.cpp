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

  add for stm32h7 by huaweiwx@sina.com 2017.12.9 
  add avr emulation  huaweiwx@sina.com 2018.9.17
*/
#include "Arduino.h"

extern "C"
void stm32GpioClockEnable(GPIO_TypeDef *port) {

#ifdef GPIOA
  if (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
#endif
#ifdef GPIOB
  if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#ifdef GPIOC
  if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
#endif
#ifdef GPIOD
  if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
#endif
#ifdef GPIOE
  if (port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
#endif
#ifdef GPIOF
  if (port == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();
#endif
#ifdef GPIOG
  if (port == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
#endif
#ifdef GPIOH
  if (port == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
#endif
#ifdef GPIOI
  if (port == GPIOI) __HAL_RCC_GPIOI_CLK_ENABLE();
#endif
#ifdef GPIOJ
  if (port == GPIOJ) __HAL_RCC_GPIOJ_CLK_ENABLE();
#endif
#ifdef GPIOK
  if (port == GPIOK) __HAL_RCC_GPIOK_CLK_ENABLE();
#endif
}

#ifndef STM32H7
extern "C"
void pinModeLL(GPIO_TypeDef *port, uint32_t ll_pin, uint8_t mode) {

  stm32GpioClockEnable(port);

  int pinMode;
  int outputType;
  int pull;

  switch ( mode ) {
    case OUTPUT:
      pinMode = LL_GPIO_MODE_OUTPUT;
      outputType = LL_GPIO_OUTPUT_PUSHPULL;
      pull = LL_GPIO_PULL_DOWN;
      break;

    case INPUT:
      pinMode = LL_GPIO_MODE_INPUT;
      outputType = LL_GPIO_OUTPUT_OPENDRAIN;
      pull = LL_GPIO_PULL_DOWN;
      break;

    case INPUT_PULLUP:
      pinMode = LL_GPIO_MODE_INPUT;
      outputType = LL_GPIO_OUTPUT_PUSHPULL;
      pull = LL_GPIO_PULL_UP;
      break;

    case INPUT_PULLDOWN:
      pinMode = LL_GPIO_MODE_INPUT;
      outputType = LL_GPIO_OUTPUT_PUSHPULL;
      pull = LL_GPIO_PULL_DOWN;
      break;

    case ANALOG:                    //add by huaweiwx@sina.com 2017.6.9
      pinMode = LL_GPIO_MODE_ANALOG;
      outputType = LL_GPIO_OUTPUT_PUSHPULL;
      pull = LL_GPIO_PULL_DOWN;
      break;

    case OUTPUT_OD:
      pinMode = LL_GPIO_MODE_OUTPUT;
      outputType = LL_GPIO_OUTPUT_OPENDRAIN;
      pull = LL_GPIO_PULL_UP;
      break;

    default:
      return;
      break;
  }

  LL_GPIO_SetPinMode(port, ll_pin, pinMode);
  LL_GPIO_SetPinPull(port, ll_pin, pull);
  LL_GPIO_SetPinOutputType(port, ll_pin, outputType);
  LL_GPIO_SetPinSpeed(port, ll_pin, LL_GPIO_SPEED_FREQ_HIGH);
}

extern "C"
void pinMode(uint8_t pin, uint8_t mode) {
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  assert_param(IS_GPIO_ALL_INSTANCE(port_pin.port));
  assert_param(IS_GPIO_PIN(port_pin.pinMask));

  if (stm32_pwm_disable_callback != NULL) {
    (*stm32_pwm_disable_callback)(port_pin.port, port_pin.pinMask);
  }

  stm32GpioClockEnable(port_pin.port);

  GPIO_InitTypeDef init;

  init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  init.Pin = port_pin.pinMask;

  switch ( mode ) {
    case OUTPUT:
      init.Mode = GPIO_MODE_OUTPUT_PP;
      init.Pull =  GPIO_NOPULL;
      break;

	case INPUT:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull =  GPIO_NOPULL;
      break;

    case INPUT_PULLUP:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull =  GPIO_PULLUP;
      break;

    case INPUT_PULLDOWN:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull = GPIO_PULLDOWN;
      break;

    case ANALOG:                    //add by huaweiwx@sina.com 2017.6.9
      init.Mode = GPIO_MODE_ANALOG;
      init.Pull = GPIO_NOPULL;
      break;

    case OUTPUT_OD:                    //add by huaweiwx@sina.com 2017.6.9
      init.Mode = GPIO_MODE_OUTPUT_OD;
      init.Pull = GPIO_NOPULL;
      break;

    default:
      assert_param(0);
      return;
      break;
  }

  HAL_GPIO_Init(port_pin.port, &init);

}

#else
	
extern "C"
void pinModeLL(GPIO_TypeDef *port, uint32_t pinMask, uint8_t mode) {
  assert_param(IS_GPIO_ALL_INSTANCE(port));
  assert_param(IS_GPIO_PIN(pinMask));

  if (stm32_pwm_disable_callback != NULL) {
    (*stm32_pwm_disable_callback)(port, pinMask);
  }
  stm32GpioClockEnable(port);

  GPIO_InitTypeDef init;

  init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  init.Pin = pinMask;

  switch ( mode ) {
    case OUTPUT:
      init.Mode = GPIO_MODE_OUTPUT_PP;
      init.Pull =  GPIO_NOPULL;
      break;

    case INPUT:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull =  GPIO_NOPULL;
      break;

    case INPUT_PULLUP:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull =  GPIO_PULLUP;
      break;

    case INPUT_PULLDOWN:
      init.Mode = GPIO_MODE_INPUT;
      init.Pull = GPIO_PULLDOWN;
      break;

    case ANALOG:                    //add by huaweiwx@sina.com 2017.6.9
      init.Mode = GPIO_MODE_ANALOG;
      init.Pull = GPIO_NOPULL;
      break;

    case OUTPUT_OD:                    //add by huaweiwx@sina.com 2017.6.9
      init.Mode = GPIO_MODE_OUTPUT_OD;
      init.Pull = GPIO_NOPULL;
      break;

    default:
      assert_param(0);
      return;
      break;
  }
  HAL_GPIO_Init(port, &init);
}

extern "C"
void pinMode(uint8_t pin, uint8_t mode) {
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  pinModeLL(port_pin.port, port_pin.pinMask, mode);
}
#endif


uint32_t pulseIn(__ConstPin cpin, bool state, uint32_t timeout )
{
  // Cache the port and bit of the pin in order to speed up the
  // pulse width measuring loop and achieve finer resolution.
  // Calling digitalRead() instead yields much coarser resolution.
  uint32_t startMicros = micros();

  // wait for any previous pulse to end
  while (digitalRead(cpin) == state) {
    if (micros()-startMicros > timeout)
      return 0;
  }

  // wait for the pulse to start
  while (digitalRead(cpin) != state) {
    if (micros()-startMicros > timeout)
      return 0;
  }

  uint32_t start = micros();
  // wait for the pulse to stop
  while (digitalRead(cpin) == state) {
    if (micros()-startMicros > timeout)
      return 0;
  }
  return (micros() - start);
}


#if USE_AVREMULATION > 0
#ifdef GPIOA
DDRemulation   DDRA(GPIOA);
#endif
#ifdef GPIOB
DDRemulation   DDRB(GPIOB);
#endif
#ifdef GPIOC
DDRemulation   DDRC(GPIOC);
#endif
#ifdef GPIOD
DDRemulation   DDRD(GPIOD);
#endif
#ifdef GPIOE
DDRemulation   DDRE(GPIOE);
#endif
#ifdef GPIOF
DDRemulation   DDRF(GPIOF);
#endif
#ifdef GPIOG
DDRemulation   DDRG(GPIOG);
#endif
#ifdef GPIOH
DDRemulation   DDRH(GPIOH);
#endif
#ifdef GPIOI
DDRemulation   DDRI(GPIOI);
#endif
#ifdef GPIOJ
DDRemulation   DDRJ(GPIOJ);
#endif
#ifdef GPIOK
DDRemulation   DDRK(GPIOK);
#endif
#endif //USE_AVREMULATION > 0

