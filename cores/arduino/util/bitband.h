/*
  huaweiwx@sina.com 2018.  All right reserved.

  for stm32 m3/m4 sram/peripheral bitband io opration
  add arduino style class BB_PIN 2017.12.20
  add LL_PIN class for all stm32 chips
  add class BB_VAR 2018.2.12
  support stm32h7x use hallib 2018.4.2

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __BITBAND_H__
#define __BITBAND_H__
#include "stm32_pin_list.h"

#define BITMASKPOS(mask) (((mask)==bit(0))?0: \
                         (((mask)==bit(1))?1: \
                         (((mask)==bit(2))?2: \
                         (((mask)==bit(3))?3: \
                         (((mask)==bit(4))?4: \
                         (((mask)==bit(5))?5: \
                         (((mask)==bit(6))?6: \
                         (((mask)==bit(7))?7: \
                         (((mask)==bit(8))?8: \
                         (((mask)==bit(9))?9: \
                         (((mask)==bit(10))?10: \
                         (((mask)==bit(11))?11: \
                         (((mask)==bit(12))?12: \
                         (((mask)==bit(13))?13: \
                         (((mask)==bit(14))?14: \
                         (((mask)==bit(15))?15:16))))))))))))))))

/*
  m0 m7 have not bitband
  STM32F3/STM32L4 GPIO unsupport bitband opration
*/
#if defined(STM32F0)||defined(STM32L0)||defined(STM32F7)||defined(STM32H7)||defined(STM32F3)||defined(STM32L4)
#  define BITBAND_OPTION 0
#else
#  define BITBAND_OPTION 1
#endif

#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))

#if BITBAND_OPTION
//bitband io opration,实现51类似的GPIO控制功能
#define BITBAND(addr, bitnum) (PERIPH_BB_BASE+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//n must be less 16!   确保n的值小于16!
//example:  in = PAin(0);
//          PCout(13) = 1;
#ifdef GPIOA
# define PAout(n)   BITBAND_ADDR((uint32_t)&(GPIOA->ODR),n)  //输出 
# define PAin(n)    BITBAND_ADDR((uint32_t)&(GPIOA->IDR),n)  //输入 
#endif
#ifdef GPIOB
# define PBout(n)   BITBAND_ADDR((uint32_t)&(GPIOB->ODR),n)  //输出 
# define PBin(n)    BITBAND_ADDR((uint32_t)&(GPIOB->IDR),n)  //输入 
#endif
#ifdef GPIOC
# define PCout(n)   BITBAND_ADDR((uint32_t)&(GPIOC->ODR),n)  //输出
# define PCin(n)    BITBAND_ADDR((uint32_t)&(GPIOC->IDR),n)  //输入
#endif
#ifdef GPIOD
# define PDout(n)   BITBAND_ADDR((uint32_t)&(GPIOD->ODR),n)  //输出
# define PDin(n)    BITBAND_ADDR((uint32_t)&(GPIOD->IDR),n)  //输入
#endif
#ifdef GPIOE
# define PEout(n)   BITBAND_ADDR((uint32_t)&(GPIOE->ODR),n)  //输出
# define PEin(n)    BITBAND_ADDR((uint32_t)&(GPIOE->IDR),n)  //输入
#endif
#ifdef GPIOF
# define PFout(n)   BITBAND_ADDR((uint32_t)&(GPIOF->ODR),n)  //输出 
# define PFin(n)    BITBAND_ADDR((uint32_t)&(GPIOF->IDR),n)  //输入
#endif
#ifdef GPIOG
# define PGout(n)   BITBAND_ADDR((uint32_t)&(GPIOG->ODR),n)  //输出 
# define PGin(n)    BITBAND_ADDR((uint32_t)&(GPIOG->IDR),n)  //输入
#endif
#ifdef GPIOH
# define PHout(n)   BITBAND_ADDR((uint32_t)&(GPIOH->ODR),n)  //输出
# define PHin(n)    BITBAND_ADDR((uint32_t)&(GPIOH->IDR),n)  //输入
#endif
#ifdef GPIOI
# define PIout(n)   BITBAND_ADDR((uint32_t)&(GPIOI->ODR),n)  //输出
# define PIin(n)    BITBAND_ADDR((uint32_t)&(GPIOI->IDR),n)  //输入
#endif

#define BB_sramVarPtr(x)  __BB_addr((volatile uint32_t*)&(x), 0, SRAM_BB_BASE, SRAM_BASE)

#ifdef __cplusplus
extern "C" {
#endif
static inline volatile uint32_t* __BB_addr(volatile void*, uint32_t, uint32_t, uint32_t);

/**
   @brief Obtain a pointer to the bit-band address corresponding to a
          bit in a volatile SRAM address.
   @param address Address in the bit-banded SRAM region
   @param bit     Bit in address to bit-band
*/
static inline volatile uint32_t* BB_sramp(volatile void *address, uint32_t bit) {
  return __BB_addr(address, bit, SRAM_BB_BASE, SRAM_BASE);
}

/**
   @brief Get a bit from an address in the SRAM bit-band region.
   @param address Address in the SRAM bit-band region to read from
   @param bit Bit in address to read
   @return bit's value in address.
*/
static inline uint8_t BB_sramGetBit(volatile void *address, uint32_t bit) {
  return *BB_sramp(address, bit);
}

/**
   @brief Set a bit in an address in the SRAM bit-band region.
   @param address Address in the SRAM bit-band region to write to
   @param bit Bit in address to write to
   @param val Value to write for bit, either 0 or 1.
*/
static inline void BB_sramSetBit(volatile void *address, uint32_t bit, uint8_t val) {
  *BB_sramp(address, bit) = val;
}

/**
   @brief Obtain a pointer to the bit-band address corresponding to a
          bit in a peripheral address.
   @param address Address in the bit-banded peripheral region
   @param bit     Bit in address to bit-band
*/
static inline volatile uint32_t* BB_perip(volatile void *address, uint32_t bit) {
  return __BB_addr(address, bit, PERIPH_BB_BASE, PERIPH_BASE);
}

/**
   @brief Get a bit from an address in the peripheral bit-band region.
   @param address Address in the peripheral bit-band region to read from
   @param bit Bit in address to read
   @return bit's value in address.
*/
static inline uint8_t BB_periGetBit(volatile void *address, uint32_t bit) {
  return *BB_perip(address, bit);
}

/**
   @brief Set a bit in an address in the peripheral bit-band region.
   @param address Address in the peripheral bit-band region to write to
   @param bit Bit in address to write to
   @param val Value to write for bit, either 0 or 1.
*/
static inline void BB_periSetBit(volatile void *address, uint32_t bit, uint8_t val) {
  *BB_perip(address, bit) = val;
}

static inline volatile uint32_t* __BB_addr(volatile void *address, uint32_t bit, uint32_t bb_base, uint32_t bb_ref) {
  return (volatile uint32_t*)(bb_base + (((uint32_t)address - bb_ref) << 5) +
                              (bit << 2));
}

static inline uint32_t BB_pinAdr(uint32_t pin, uint8_t mode) {
  uint32_t portaddr = ((mode) ? ((uint32_t) &variant_pin_list[pin].port->ODR)
                       : ((uint32_t) &variant_pin_list[pin].port->IDR));
  uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask) - 1;
  return BITBAND(portaddr, bit);
}

static inline uint32_t BB_pinInAdr(uint32_t pin) {
  uint32_t portaddr = (uint32_t) &variant_pin_list[pin].port->IDR;
  uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask) - 1;
  return BITBAND(portaddr, bit);
}

static inline uint32_t BB_pinOutAdr(uint32_t pin) {
  uint32_t portaddr = (uint32_t) &variant_pin_list[pin].port->ODR;
  uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask) - 1;
  return BITBAND(portaddr, bit);
}
#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITBAND_OPTION

#ifdef __cplusplus

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"

#if BITBAND_OPTION
/*gpio bitband interface class*/
class BB_PIN {
  public:
    BB_PIN(__ConstPin CPin): CPin(CPin) {}
    __ConstPin CPin;

#ifdef STM32F1
    /*F1 ll_gpio_pin to gpio_pin :  (ll_gpio_pin>>GPIO_PIN_MASK_POS) & 0x0000FFFFU*/
	const uint8_t  pos       = POSITION_VAL((CPin.pinMask >> GPIO_PIN_MASK_POS) & 0x0000FFFFU);
#else
    const uint8_t  pos       = POSITION_VAL(CPin.pinMask); //  __builtin_ffs(CPin.pinMask) - 1;
#endif

    const uint32_t inReg     = (const uint32_t)&((GPIO_TypeDef*)CPin.ulPortBase)->IDR;
    const uint32_t outReg    = (const uint32_t)&((GPIO_TypeDef*)CPin.ulPortBase)->ODR;
    const uint32_t bb_inadr  = BITBAND(inReg, pos);
    const uint32_t bb_outadr = BITBAND(outReg, pos);

    template<typename T = bool>
    inline T read() {
      return MEM_ADDR(this->bb_inadr);
    }

    template<typename T>
    inline  void write(T value) {
      MEM_ADDR(this->bb_outadr) =(bool)value;
    }

    template<typename T>
    inline BB_PIN & operator = (T value) {
      this->write(value);
      return *this;
    }
	
    template<typename T>
    inline BB_PIN & operator ^= (T value) {
      if(value) this->toggle();
      return *this;
    }
    inline BB_PIN& operator = (BB_PIN& rhs) {
      this->write(rhs.read());
      return *this;
    }

    inline void high() {
      MEM_ADDR(this->bb_outadr) = 1;
    }

    inline void low() {
      MEM_ADDR(this->bb_outadr) = 0;
    }

    inline operator bool () __attribute__((always_inline)) {
      return (MEM_ADDR(this->bb_inadr));
    }


    inline void operator  !() __attribute__((always_inline)) {
      this->toggle();
    }

    /*----- comptabled with DigitalPin ----------*/
    inline __attribute__((always_inline))
    void toggle() {
		digitalToggle(CPin);
    }

    inline __attribute__((always_inline))
    void config(uint8_t mode, bool value) {  /*compatale with digitalPin*/
      this->mode(mode);
      this->write(value);
    }

    inline __attribute__((always_inline))
    void mode(uint8_t mode) {
      pinMode(CPin, mode);
    }

    inline __attribute__((always_inline))
    void attach(voidFuncPtr callback, uint8_t mode) {
      attachInterrupt(CPin, callback, mode);
    }

    inline __attribute__((always_inline))
    void detach(void) {
      detachInterrupt(CPin);
    }

};

#else
#  define BB_PIN LL_PIN  /*m0/7 use LL_PIN class*/
#endif //BITBAND_OPTION

#pragma GCC diagnostic pop

#if BITBAND_OPTION
template<class T>
class BB_VAR {
  public:
    T val;
    inline  operator T() __attribute__((always_inline)) {
      return this->val;
    };
    inline  BB_VAR& operator = (T value) __attribute__((always_inline)) {
      this->val = value;
      return *this;
    };
    volatile  uint32_t* bit = BB_sramVarPtr(val);
};
#endif

template<const int gpioBase, const uint16_t mask = 0xffff, const uint32_t mode = INPUT>
class PORTIO {
  private:
    GPIO_InitTypeDef GPIO_InitStruct;


  public:

    constexpr uint16_t nmask(void) {
      return ~mask;
    }

    PORTIO() {
      GPIO_InitStruct.Pin = mask;
      setSpeed(GPIO_SPEED_FREQ_VERY_HIGH);
      setMode((uint32_t)mode); //default mode INPUT
    }

    void Init(void) {
      clockOn();
      HAL_GPIO_Init((GPIO_TypeDef *)gpioBase, &GPIO_InitStruct);
    }

    void Init(uint32_t md) {
      setMode(md);
      Init();
    }

    void outPut(void) {
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      HAL_GPIO_Init((GPIO_TypeDef *)gpioBase, &GPIO_InitStruct);
    }

    void inPut(void) {
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      HAL_GPIO_Init((GPIO_TypeDef *)gpioBase, &GPIO_InitStruct);
    }


    inline void clockOn() {
      stm32GpioClockEnable((GPIO_TypeDef *)gpioBase);
    }

    void setMode(uint32_t md) {
      switch ( md ) {
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
          GPIO_InitStruct.Pull =  GPIO_PULLDOWN;
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
          break;
      }
    }

    inline void setSpeed(uint32_t s) {
      GPIO_InitStruct.Speed = s;
    }

    inline GPIO_InitTypeDef* getInitParam() {
      return &GPIO_InitStruct;
    }

    void write(uint16_t val) {
      val &= mask;
      val |= ((GPIO_TypeDef *)gpioBase)->ODR & nmask();
      ((GPIO_TypeDef *)gpioBase)->ODR = val;
    }

    uint16_t read(void) {
      return (((GPIO_TypeDef *)gpioBase)->IDR & mask);
    }

    operator uint16_t () {
      return read();
    }

    PORTIO& operator = (uint16_t value) {
      write(value);
      return *this;
    }

    PORTIO& operator= (PORTIO& rhs) {
      write(rhs.read());
      return *this;
    }

};

#if 0

template<uint32_t gpioBase>
class GPIOPINRef {
  public:

    GPIOPINRef<gpioBase>( const int index )
      : index( index )                 {}

    //Access/read members.
    bool operator*() const            {
      return HAL_GPIO_ReadPin((GPIO_TypeDef*)(gpioBase), 1 << index);
    }
    operator const bool () const       {
      return **this;
    }

    //Assignment/write members.
    GPIOPINRef<gpioBase> &operator=( const GPIOPINRef<gpioBase> &ref ) {
      return *this = *ref;
    }
    GPIOPINRef<gpioBase> &operator=( bool in )       {
      HAL_GPIO_WritePin((GPIO_TypeDef*)(gpioBase), 1 << index , (in ? 1 : 0));
      return *this;
    }

    int index;
};

template<uint32_t gpioBase>
class GPIOPINPtr {
  public:

    GPIOPINPtr<gpioBase>( const int index ): index( index ) {}

    operator const int() const          {
      return index;
    }
    GPIOPINPtr<gpioBase> &operator=( int in )          {
      return index = in, *this;
    }

    //Iterator functionality.
    bool operator!=( const GPIOPINPtr &ptr ) {
      return index != ptr.index;
    }
    GPIOPINRef<gpioBase> operator*()                   {
      return index;
    }

    int index;
};

template<uint32_t gpioBase>
class GPIOPORTClass {
  public:

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_TypeDef  *GPIOx;
    void port_init(int mask, PinDirection dir)
    {
      uint32_t port_index = (uint32_t)port;

      // Enable GPIO clock
      uint32_t gpio_add = Set_GPIO_Clock(port_index);
      GPIO_TypeDef *gpio = (GPIO_TypeDef *)gpio_add;

      // Fill PORT object structure for future use
      obj->port      = port;
      obj->mask      = mask;
      obj->direction = dir;
      obj->reg_in    = &gpio->IDR;
      obj->reg_out   = &gpio->ODR;

      port_dir(obj, dir);
    }

    GPIOPINRef<gpioBase> operator[]( const int idx )    {
      return idx;
    }

    operator uint16_t () {
      return this->read();
    };

    GPIOPORTClass &operator = (uint16_t value) {
      this->write(value);
      return *this;
    };

    inline void write(uint16_t val) {
      ((GPIO_TypeDef*)(gpioBase))->ODR = val;
    };

    inline uint16_t read() {
      return ((GPIO_TypeDef*)(gpioBase))->IDR;
    };
};
#endif

#endif //__cplusplus
#endif //__BITBAND_H__
