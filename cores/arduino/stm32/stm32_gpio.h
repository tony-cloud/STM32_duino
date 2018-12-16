/*
  Copyright (c) 2017 Daniel Fekete
  add avr emulation and gpio fastIO 2017 huaweiwx@sina.com

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

#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include "stm32_def.h"
#include "stm32_pin_list.h"
#include "variant.h"
#include "stm32_HAL/stm32XXxx_ll_gpio.h"
#include "stm32_clock.h"
#include "util/base.h"
#include "core_callback.h"

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3

#define ANALOG 0x04

#define OUTPUT_PP 0x1    /* as OUTPUT add by huaweiwx@sina.com 2017.6.9   */
#define OUTPUT_OD 0x11   /*!< Output Open Drain Mode  add by huaweiwx@sina.com 2017.6.9   */


#ifndef GPIO_SPEED_FREQ_VERY_HIGH
#define GPIO_SPEED_FREQ_VERY_HIGH GPIO_SPEED_FREQ_HIGH
#endif

#define RwReg  uint32_t

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  GPIO_TypeDef *port;
  uint32_t pinMask;
} stm32_port_pin_type;

typedef uint32_t (*stm32_clock_freq_func)();

typedef struct {
  void *instance;
  stm32_clock_freq_func clock_freq_func;
} stm32_clock_freq_list_type;

extern const stm32_port_pin_type variant_pin_list[NUM_DIGITAL_PINS];

inline GPIO_TypeDef* pinToPort(uint8_t pin) {
  return variant_pin_list[pin].port; /* equal_to digitalPinToPort(pin)*/
}
inline uint32_t pinToBitMask(uint8_t pin) {
  return variant_pin_list[pin].pinMask; /* equal_to digitalPinToBitMask(pin)*/
}


/**
   Start clock for the fedined port
*/
void stm32GpioClockEnable(GPIO_TypeDef *port);

/**
   If PWM is used at least once, this method is set to the PWM disable function in stm32_PWM.c
*/
typedef void (*stm32_pwm_disable_callback_func)(GPIO_TypeDef *port, uint32_t pin);
extern stm32_pwm_disable_callback_func stm32_pwm_disable_callback;

extern void attachInterrupt(uint8_t, void (*)(void), int mode);
extern void detachInterrupt(uint8_t);

inline void digitalWriteHigh(uint8_t pin) {
  //    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
  //        return;
  //    }
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  HAL_GPIO_WritePin(port_pin.port, port_pin.pinMask, GPIO_PIN_SET);
}
inline void digitalWriteLow(uint8_t pin) {
  //    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
  //        return;
  //    }
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  HAL_GPIO_WritePin(port_pin.port, port_pin.pinMask, GPIO_PIN_RESET);
}

inline void digitalWrite(uint8_t pin, uint8_t value) {
  //    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
  //        return;
  //    }
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  HAL_GPIO_WritePin(port_pin.port, port_pin.pinMask, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
inline int digitalRead(uint8_t pin) {
  //    if (pin >= sizeof(variant_pin_list) / sizeof(variant_pin_list[0])) {
  //        return 0;
  //    }

  stm32_port_pin_type port_pin = variant_pin_list[pin];
  return HAL_GPIO_ReadPin(port_pin.port, port_pin.pinMask);
}

inline void digitalToggle(uint8_t pin) {
  stm32_port_pin_type port_pin = variant_pin_list[pin];
  HAL_GPIO_TogglePin(port_pin.port, port_pin.pinMask);
}

#ifdef __cplusplus
}
#endif


#define PIN(a, b)   b
static const uint8_t variant_gpiopin_pos_static[] = {
  PIN_LIST
};
#undef PIN

#ifndef STM32H7
#define PIN(a, b) { GPIO##a , LL_GPIO_PIN_##b }
static const stm32_port_pin_type variant_pin_list_ll_static[] = {
  PIN_LIST
};
#undef PIN
#endif

#ifdef __cplusplus

inline static void digitalWriteHigh(__ConstPin CPin) {
  LL_GPIO_SetOutputPin((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
}
inline static void digitalWriteLow(__ConstPin CPin) {
  LL_GPIO_ResetOutputPin((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
}

template<typename T>
inline static void digitalWrite(__ConstPin CPin, T value) {
  if (value) {
    LL_GPIO_SetOutputPin((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
  } else {
    LL_GPIO_ResetOutputPin((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
  }
}

template<typename T = bool>
inline static T digitalRead(__ConstPin CPin) {
  return LL_GPIO_IsInputPinSet((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
}

extern "C" void pinModeLL(GPIO_TypeDef *port, uint32_t ll_pin, uint8_t mode);
inline static void pinMode(__ConstPin CPin, uint8_t mode) {
#ifdef STM32F1
  pinMode(CPin.ucPin,mode); 
#else	
  pinModeLL((GPIO_TypeDef *)CPin.ulPortBase, CPin.pinMask, mode);
#endif
}

inline static void digitalToggle(__ConstPin CPin) {
  LL_GPIO_TogglePin((GPIO_TypeDef*)CPin.ulPortBase, CPin.pinMask);
}

#if USE_AVREMULATION > 0

class DDRemulation
{
  public:
    DDRemulation(GPIO_TypeDef *port, uint16_t mask = 0xffff): port(port), mask(mask) {}
    GPIO_TypeDef *port;
    uint16_t mask;

	inline void setMask(uint16_t val){
		mask = val;
	}
	inline uint16_t getMask(void){
		return mask;
	}
	inline void lock(uint16_t pinMask){
		this->saveddr &= ~pinMask;
	}
	inline void unLock(uint16_t pinMask){
		this->saveddr |= (pinMask & mask);
	}
    void mode(int pins, uint8_t mode) {
      if (this->inited == 0) {
        stm32GpioClockEnable(port);
        this->inited = 1;
      }
      gpio_init(pins, mode);
    }
    inline operator int () {
      return this->saveddr;
    }
    inline DDRemulation & operator = (int pins) __attribute__((always_inline)) {
      this->gpio_init(pins,  OUTPUT);
      this->gpio_init(~pins,  INPUT);
      return *this;
    }
    inline DDRemulation & operator |= (int pins) __attribute__((always_inline)) {
      this->gpio_init(pins, OUTPUT);
      return *this;
    }
    inline DDRemulation & operator &= (int pins) __attribute__((always_inline)) {
      this->gpio_init(~pins, INPUT);
      return *this;
    }

  private:
    uint8_t inited = 0;
    uint16_t saveddr = 0;

    void gpio_init(int pins, uint8_t mode) {
      GPIO_InitTypeDef GPIO_InitStruct;

      switch ( mode ) {
        case INPUT:
          GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull =  GPIO_NOPULL;
          break;

        case INPUT_PULLUP:
          GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull =  GPIO_PULLUP;
          break;

        case INPUT_PULLDOWN:
          GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
          GPIO_InitStruct.Pull = GPIO_PULLDOWN;
          break;

        case ANALOG:
          GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
          GPIO_InitStruct.Pull = GPIO_NOPULL;
          break;

        case OUTPUT:
          GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
          GPIO_InitStruct.Pull =  GPIO_NOPULL;
          break;

        case OUTPUT_OD:
          GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
          GPIO_InitStruct.Pull = GPIO_NOPULL;
          break;

        default:
          assert_param(0);
          return;
          break;
      }
      GPIO_InitStruct.Pin = pins & mask;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      HAL_GPIO_Init(port, &GPIO_InitStruct);

      if ((mode == OUTPUT) || (mode == OUTPUT_OD)) saveddr |= GPIO_InitStruct.Pin;
      else   saveddr &= ~GPIO_InitStruct.Pin;

      saveddr &= mask;
    }
};

class PORTemulation
{
  public:
    PORTemulation(GPIO_TypeDef *port): port(port) {}
    GPIO_TypeDef *port;
 
    inline operator int () const __attribute__((always_inline)) {
      return port->ODR;
    }
    inline PORTemulation & operator = (uint16_t pins) __attribute__((always_inline)) {
      port->ODR = pins;
      return *this;
    }
    inline PORTemulation & operator ^= (uint16_t pins) __attribute__((always_inline)) {
      port->ODR ^= pins;
      return *this;
    }
#ifndef STM32H7	
    inline PORTemulation & operator |= (int pins) __attribute__((always_inline)) {
      port->BSRR = pins;
      return *this;
    }
    inline PORTemulation & operator &= (int pins) __attribute__((always_inline)) {
      port->BSRR = (~pins) << 16U;
      return *this;
    }
#else
    inline PORTemulation & operator |= (int pins) __attribute__((always_inline)) {
      port->BSRRL = pins;
      return *this;
    }
    inline PORTemulation & operator &= (int pins) __attribute__((always_inline)) {
      port->BSRRH = ~pins;
      return *this;
    }
#endif
};

class PINemulation
{
  public:
    PINemulation(GPIO_TypeDef *port): port(port) {}
    GPIO_TypeDef *port;
 
    inline operator uint32_t () {
      return port->IDR;
    }
};

#ifdef GPIOA
extern DDRemulation   DDRA;
#endif
#ifdef GPIOB
extern DDRemulation   DDRB;
#endif
#ifdef GPIOC
extern DDRemulation   DDRC;
#endif
#ifdef GPIOD
extern DDRemulation   DDRD;
#endif
#ifdef GPIOE
extern DDRemulation   DDRE;
#endif
#ifdef GPIOF
extern DDRemulation   DDRF;
#endif
#ifdef GPIOG
extern DDRemulation   DDRG;
#endif
#ifdef GPIOH
extern DDRemulation   DDRH;
#endif
#ifdef GPIOI
extern DDRemulation   DDRI;
#endif
#ifdef GPIOJ
extern DDRemulation   DDRJ;
#endif
#ifdef GPIOK
extern DDRemulation   DDRK;
#endif

#endif //USE_AVREMULATION > 0

/*gpio low layer interface class*/
class LL_PIN {
  public:
    constexpr LL_PIN(__ConstPin CPin): CPin(CPin) {}
    __ConstPin CPin;
	
    template<typename T>
    inline LL_PIN & operator = (T value) {
      this->write(value);
      return *this;
    }
    template<typename T>
    inline LL_PIN & operator ^= (T value) {
      if(value) this->toggle();
      return *this;
    }

    LL_PIN& operator = (LL_PIN& rhs) {
      this->write(rhs.read());
      return *this;
    }

    template<typename T>
    inline void write(T value) {
      digitalWrite(CPin, value);
    }

    inline __attribute__((always_inline))
    void high() {
      digitalWriteHigh(CPin);
    }

    inline __attribute__((always_inline))
    void low() {
      digitalWriteLow(CPin);
    }

    template<typename T = bool>
    inline operator T () const {
      return this->read();
    }

    template<typename T = bool>
    inline T read() const {
      return digitalRead(CPin);
    }

    inline void operator  !() __attribute__((always_inline)) {
      this->toggle();
    }

    /*----- comptabled with DigitalPin ----------*/
    inline __attribute__((always_inline))
    void toggle() {
      digitalToggle(CPin);
    }

    template<typename T>
    inline  void config(uint8_t mode, T level) {  /*compatale with digitalPin*/
      this->mode(mode);
      this->write(level);
    }

    inline void mode(uint8_t mode) {
      pinMode(CPin, mode);
    }

    inline void attach(voidFuncPtr callback, uint8_t mode) {
      attachInterrupt(CPin.ucPin, callback, mode);
    }

    inline void detach(void) {
      detachInterrupt(CPin.ucPin);
    }

};

uint32_t pulseIn(__ConstPin CPin, bool state = false, uint32_t timeout = 1'000'000L );

class InputPin : public LL_PIN {
  public:
    uint32_t ulDelayCnt = F_CPU / 10'000'000;  
    constexpr InputPin(__ConstPin CPin, bool initial_value = 1): LL_PIN(CPin) {
      config(INPUT, initial_value);
    }

    inline void setWaitTime(uint32_t time){
		ulDelayCnt = time;
	}

    template<typename T = bool>
    inline operator T () const {
      /*Waiting for stability*/
      if (ulDelayCnt) {                           
        for (volatile uint32_t i = ulDelayCnt; i > 0; i--);
      }
       return read();
    }

    uint32_t pulseIn(bool state = false, uint32_t timeout = 1'000'000L )
    {
      // Cache the port and bit of the pin in order to speed up the
      // pulse width measuring loop and achieve finer resolution.
      // Calling digitalRead() instead yields much coarser resolution.
      uint32_t startMicros = micros();
      // wait for any previous pulse to end
      while (read() == state) {
        if (micros() - startMicros > timeout)
          return 0;
      }

      // wait for the pulse to start
      while (read() != state) {
        if (micros() - startMicros > timeout)
          return 0;
      }

      uint32_t start = micros();
      // wait for the pulse to stop
      while (read() == state) {
        if (micros() - startMicros > timeout)
          return 0;
      }
      return (micros() - start);
    }
};


class OutputPin : public LL_PIN {
  public:
    uint32_t ulDelayCnt = F_CPU / 10'000'000;

	constexpr OutputPin(__ConstPin CPin, bool initial_value = 0): LL_PIN(CPin) {
      config(OUTPUT, initial_value);
    }

    inline void setWaitTime(uint32_t time){
		ulDelayCnt = time;
	}

    void pulse(bool value = true) {
      if (ulDelayCnt) {
        for (volatile uint32_t i = ulDelayCnt; i > 0; i--);
      }
      this->write(value);
      if (ulDelayCnt) {
        for (volatile uint32_t i = ulDelayCnt; i > 0; i--);
      }
      this->toggle();
    }

    template<typename T = bool>
    inline operator T () const {
       return read();
    }
 
    inline void operator  !() __attribute__((always_inline)) {
      toggle();
	}
	
    template<typename T>
    inline OutputPin & operator = (T value) {
       write(value);
      return *this;
    }
    template<typename T>
    inline OutputPin & operator ^= (T value) {
      if(value) toggle();
      return *this;
    }
};

template < uint8_t nbits = 8, uint8_t bit_order = MSBFIRST>
class ClockedInput {
    // A DirectIO implementation of shiftIn. Also supports
    // a variable number of bits (1-32); shiftIn is always 8 bits.
  public:
    // Define a type large enough to hold nbits bits (see base.h)
    typedef bits_type(nbits) bits_t;
	
    uint32_t ulDelayCnt = F_CPU / 10'000'000;

    constexpr ClockedInput(__ConstPin data_pin, __ConstPin clock_pin , bool pullup = true) : data(data_pin, pullup), clock(clock_pin) {}
    InputPin  data;
    OutputPin clock;

    inline void setWaitTime(uint32_t time){
		ulDelayCnt = time;
	}

    bits_t read() {
      // read nbits bits from the input pin and pack them
      // into a value of type bits_t.

      bits_t value = 0;
      bits_t mask = (bit_order == LSBFIRST) ? 1 : (bits_t(1) << (nbits - 1));

      data.setWaitTime(0);  /*use this ulDelayCnt*/

      for (uint8_t i = 0; i < nbits; i++) {
        clock = HIGH;
        if (ulDelayCnt) {
          for (volatile uint32_t i = ulDelayCnt; i > 0; i--);
        }

        if (data) {
          value |= mask;
        }

        clock = LOW;

        if (bit_order == LSBFIRST) {
          mask <<= 1;
        }
        else {
          mask >>= 1;
        }
        if (ulDelayCnt) {
          for (volatile uint32_t i = ulDelayCnt; i > 0; i--);
        }
      }
      return value;
    }

    operator bits_t() {
      return read();
    }
};

template < uint8_t nbits = 8, uint8_t bit_order = MSBFIRST>
class ClockedOutput {
    // A DirectIO implementation of shiftOut. Also supports
    // a variable number of bits (1-32); shiftOut is always 8 bits.
  public:
    // Define a type large enough to hold nbits bits (see base.h)
    typedef bits_type(nbits) bits_t;
    uint32_t ulDelayCnt = F_CPU / 10'000'000;

    constexpr ClockedOutput(__ConstPin data_pin, __ConstPin clock_pin): data(data_pin), clock(clock_pin) {};
    OutputPin data;
    OutputPin clock;

    inline void setWaitTime(uint32_t time){
		ulDelayCnt = time;
	}

    void write(bits_t val, bool level = HIGH) {
      // write nbits bits to the output pin
      bits_t mask = (bit_order == LSBFIRST) ? 1 : (bits_t(1) << (nbits - 1));

      clock.setWaitTime(ulDelayCnt);  /*setup clock.pulse width*/

      for (uint8_t i = 0; i < nbits; i++) {
        data = (val & mask);
        clock.pulse(level);

        if (bit_order == LSBFIRST) {
          mask <<= 1;
        }
        else {
          mask >>= 1;
        }
      }
    }

    ClockedOutput& operator = (bits_t val) {
      write(val);
      return *this;
    }
};

#define GPIOPIN  LL_PIN
// This macro lets you temporarily set an output to a value, 
// and toggling back at the end of the code block. For example:
// 
// Output<2> cs;
// Output<3> data;
// with(cs, LOW) {
//     data = HIGH;
// }
// 
// is equivalent to:
// cs = LOW;
// data = HIGH;
// cs = HIGH;

#define with(pin, val) for(boolean _loop_##pin=((pin=val),true);_loop_##pin; _loop_##pin=((pin=!val), false))


#endif /* __cplusplus */

#if USE_AVREMULATION > 0
/*compatable with avr*/
#ifdef GPIOA
# define PORTA      GPIOA->ODR
# define PINA       GPIOA->IDR
#endif
#ifdef GPIOB
# define PORTB      GPIOB->ODR
# define PINB       GPIOB->IDR
#endif
#ifdef GPIOC
# define PORTC      GPIOC->ODR
# define PINC       GPIOC->IDR
#endif
#ifdef GPIOD
# define PORTD      GPIOD->ODR
# define PIND       GPIOD->IDR
#endif
#ifdef GPIOE
# define PORTE      GPIOE->ODR
# define PINE       GPIOE->IDR
#endif
#ifdef GPIOF
# define PORTF      GPIOF->ODR
# define PINF       GPIOF->IDR
#endif
#ifdef GPIOG
# define PORTG      GPIOG->ODR
# define PING       GPIOG->IDR
#endif
#ifdef GPIOH
# define PORTH      GPIOH->ODR
# define PINH       GPIOH->IDR
#endif
#ifdef GPIOI
# define PORTI      GPIOI->ODR
# define PINI       GPIOI->IDR
#endif

#endif /*USE_AVREMULATION*/

#if USE_BITBAND >0
#include "util/bitband.h"
#endif

#include "stm32_ADC.h"

#endif //STM32_GPIO_H
