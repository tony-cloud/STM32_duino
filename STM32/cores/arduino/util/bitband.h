/* 
  huaweiwx@sina.com 2017.  All right reserved.

  for stm32 m3/m4 sram/peripheral bitband io opration
  for all stm32 chips 2017.5.28
  add BB functions from maple 2017.10.12 
  add arduino style class BB_PIN 2017.12.20
  for stm32 m0/7 LL_PIN class 
  
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

#define BITMASKPOS(mask)    (((mask)==bit(0))?0: \
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

#if (defined(STM32F0)||defined(STM32L0)||defined(STM32F7))
#define BITBAND_OPTION 0
#else
#define BITBAND_OPTION 1 
#endif

#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 

#ifdef GPIOA
#define PORTA      GPIOA->ODR    //输出 
#define PINA       GPIOA->IDR    //输入 
#endif
#ifdef GPIOB
#define PORTB      GPIOB->ODR    //输出 
#define PINB       GPIOB->IDR    //输入 
#endif
#ifdef GPIOC
#define PORTC      GPIOC->ODR                  //输出 
#define PINC       GPIOC->IDR                  //输入 
#endif
#ifdef GPIOD
#define PORTD      GPIOD->ODR    //输出 
#define PIND       GPIOD->IDR    //输入 
#endif
#ifdef GPIOE
#define PORTE      GPIOE->ODR    //输出 
#define PINE       GPIOE->IDR    //输入 
#endif
#ifdef GPIOF
#define PORTF      GPIOF->ODR    //输出 
#define PINF       GPIOF->IDR    //输入 
#endif
#ifdef GPIOG
#define PORTG      GPIOG->ODR    //输出 
#define PING       GPIOG->IDR    //输入 
#endif
#ifdef GPIOH
#define PORTH      GPIOH->ODR    //输出 
#define PINH       GPIOH->IDR    //输入 
#endif
#ifdef GPIOI
#define PORTI      GPIOI->ODR    //输出 
#define PINI       GPIOI->IDR    //输入 
#endif

#if BITBAND_OPTION
//bitband io opration,实现51类似的GPIO控制功能
#define BITBAND(addr, bitnum) (PERIPH_BB_BASE+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//n must be less 16!   确保n的值小于16!
//example:  in = PAin(0);  
//          PCout(13) = 1;
#ifdef GPIOA
#define PAout(n)   BITBAND_ADDR((uint32_t)&GPIOA->ODR,n)  //输出 
#define PAin(n)    BITBAND_ADDR((uint32_t)&GPIOA->IDR,n)  //输入 
#endif
#ifdef GPIOB
#define PBout(n)   BITBAND_ADDR((uint32_t)&GPIOB->ODR,n)  //输出 
#define PBin(n)    BITBAND_ADDR((uint32_t)&GPIOB->IDR,n)  //输入 
#endif
#ifdef GPIOC
#define PCout(n)   BITBAND_ADDR((uint32_t)&GPIOC->ODR,n)  //输出 
#define PCin(n)    BITBAND_ADDR((uint32_t)&GPIOC->IDR,n)  //输入 
#endif
#ifdef GPIOD
#define PDout(n)   BITBAND_ADDR((uint32_t)&GPIOD->ODR,n)  //输出 
#define PDin(n)    BITBAND_ADDR((uint32_t)&GPIOD->IDR,n)  //输入 
#endif
#ifdef GPIOE
#define PEout(n)   BITBAND_ADDR((uint32_t)&GPIOE->ODR,n)  //输出 
#define PEin(n)    BITBAND_ADDR((uint32_t)&GPIOE->IDR,n)  //输入
#endif
#ifdef GPIOF
#define PFout(n)   BITBAND_ADDR((uint32_t)&GPIOF->ODR,n)  //输出 
#define PFin(n)    BITBAND_ADDR((uint32_t)&GPIOF->IDR,n)  //输入
#endif
#ifdef GPIOG
#define PGout(n)   BITBAND_ADDR((uint32_t)&GPIOG->ODR,n)  //输出 
#define PGin(n)    BITBAND_ADDR((uint32_t)&GPIOG->IDR,n)  //输入
#endif
#ifdef GPIOH
#define PHout(n)   BITBAND_ADDR((uint32_t)&GPIOH->ODR,n)  //输出 
#define PHin(n)    BITBAND_ADDR((uint32_t)&GPIOH->IDR,n)  //输入
#endif
#ifdef GPIOI
#define PIout(n)   BITBAND_ADDR((uint32_t)&GPIOI->ODR,n)  //输出 
#define PIin(n)    BITBAND_ADDR((uint32_t)&GPIOI->IDR,n)  //输入
#endif

//for arduino pin add 2017.10
#define PIN_OUTADR(n) BITBAND(((const uint32_t)&variant_pin_list[n].port->ODR),\
                              BITMASKPOS(variant_pin_list[n].pinMask))

#define PIN_INADR(n)  BITBAND(((const uint32_t)&variant_pin_list[n].port->IDR),\
                              BITMASKPOS(variant_pin_list[n].pinMask))

#define PINOut(pin)	MEM_ADDR(PIN_OUTADDR(pin))						
#define PINin(pin)	MEM_ADDR(PIN_OUTADDR(pin))

#define BB_sramVarPtr(x)  __BB_addr((volatile uint32_t*)&(x), 0, SRAM_BB_BASE, SRAM_BASE)

#ifdef __cplusplus
extern "C" {
#endif
static inline volatile uint32_t* __BB_addr(volatile void*,
                                         uint32_t,
                                         uint32_t,
                                         uint32_t);

/**
 * @brief Obtain a pointer to the bit-band address corresponding to a
 *        bit in a volatile SRAM address.
 * @param address Address in the bit-banded SRAM region
 * @param bit     Bit in address to bit-band
 */
static inline volatile uint32_t* BB_sramp(volatile void *address, uint32_t bit) {
    return __BB_addr(address, bit, SRAM_BB_BASE, SRAM_BASE);
}

/**
 * @brief Get a bit from an address in the SRAM bit-band region.
 * @param address Address in the SRAM bit-band region to read from
 * @param bit Bit in address to read
 * @return bit's value in address.
 */
static inline uint8_t BB_sramGetBit(volatile void *address, uint32_t bit) {
    return *BB_sramp(address, bit);
}

/**
 * @brief Set a bit in an address in the SRAM bit-band region.
 * @param address Address in the SRAM bit-band region to write to
 * @param bit Bit in address to write to
 * @param val Value to write for bit, either 0 or 1.
 */
static inline void BB_sramSetBit(volatile void *address,
                                   uint32_t bit,
                                   uint8_t val) {
    *BB_sramp(address, bit) = val;
}

/**
 * @brief Obtain a pointer to the bit-band address corresponding to a
 *        bit in a peripheral address.
 * @param address Address in the bit-banded peripheral region
 * @param bit     Bit in address to bit-band
 */
static inline volatile uint32_t* BB_perip(volatile void *address, uint32_t bit) {
    return __BB_addr(address, bit, PERIPH_BB_BASE, PERIPH_BASE);
} 

/**
 * @brief Get a bit from an address in the peripheral bit-band region.
 * @param address Address in the peripheral bit-band region to read from
 * @param bit Bit in address to read
 * @return bit's value in address.
 */
static inline uint8_t BB_periGetBit(volatile void *address, uint32_t bit) {
    return *BB_perip(address, bit);
}

/**
 * @brief Set a bit in an address in the peripheral bit-band region.
 * @param address Address in the peripheral bit-band region to write to
 * @param bit Bit in address to write to
 * @param val Value to write for bit, either 0 or 1.
 */
static inline void BB_periSetBit(volatile void *address,
                                   uint32_t bit,
                                   uint8_t val) {
    *BB_perip(address, bit) = val;
}

static inline volatile uint32_t* __BB_addr(volatile void *address,
                                         uint32_t bit,
                                         uint32_t bb_base,
                                         uint32_t bb_ref) {
    return (volatile uint32_t*)(bb_base + (((uint32_t)address - bb_ref)<<5) +
                              (bit<<2));
}

static inline uint32_t BB_pinAdr(uint32_t pin,uint8_t mode){
	uint32_t portaddr =((mode)?((uint32_t) &variant_pin_list[pin].port->ODR)
	                          :((uint32_t) &variant_pin_list[pin].port->IDR));
	uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask)-1;
	return BITBAND(portaddr,bit);
}

static inline uint32_t BB_pinInAdr(uint32_t pin){
	uint32_t portaddr = (uint32_t) &variant_pin_list[pin].port->IDR;
	uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask)-1;
	return BITBAND(portaddr,bit);
}

static inline uint32_t BB_pinOutAdr(uint32_t pin){
	uint32_t portaddr = (uint32_t) &variant_pin_list[pin].port->ODR;
	uint32_t bit = __builtin_ffs(variant_pin_list[pin].pinMask)-1;
	return BITBAND(portaddr,bit);
}
#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITBAND_OPTION

#ifdef __cplusplus

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
template<const int PinNumber>
class LL_PIN{
 public:
  //----------------------------------------------------------------------------
  constexpr const uint8_t  pos(void){return variant_gpiopin_pos_static[PinNumber];};
  constexpr const uint32_t base(void){return variant_gpiopin_base_static[PinNumber];};

  inline LL_PIN & operator = (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }
  
  inline LL_PIN & operator << (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }
  
  template<class T> 
  inline LL_PIN & operator >> (T &value){
    value = this->read();
    return *this;
  }

  inline __attribute__((always_inline))
  void write(bool value){
    if (value) {
        LL_GPIO_SetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
    } else {
        LL_GPIO_ResetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
    }
  }

  inline __attribute__((always_inline))
  void high(){LL_GPIO_SetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));}

  inline __attribute__((always_inline))
  void low(){LL_GPIO_ResetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));}

  inline operator bool () const __attribute__((always_inline)) {
    return this->read();
  }

  inline __attribute__((always_inline))
  bool read() const{return LL_GPIO_IsInputPinSet((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));}

/*----- comptabled with DigitalPin ----------*/
  inline __attribute__((always_inline))
  void toggle(){LL_GPIO_TogglePin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));}

  inline __attribute__((always_inline))
  void config(uint8_t mode, bool level) {
      this->write(level);
	  this->mode(mode);
  }

  inline __attribute__((always_inline))
  void mode(uint8_t mode){
	  pinModeLL((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber), mode);}
};

#if BITBAND_OPTION
template<const int PinNumber>
class BB_PIN{
 public:
  //----------------------------------------------------------------------------
  constexpr const uint8_t  pos(void){return variant_gpiopin_pos_static[PinNumber];};
  constexpr const uint32_t base(void){return variant_gpiopin_base_static[PinNumber];};
#ifdef STM32F1
  constexpr const uint32_t pinReg(void){return this->base()+8;};
  constexpr const uint32_t portReg(void){return this->base()+12;};
#else
  constexpr const uint32_t pinReg(void){return this->base()+16;};
  constexpr const uint32_t portReg(void){return this->base()+20;};
#endif
  constexpr const uint32_t bb_inadr(void){return BITBAND(this->pinReg(),this->pos());};
  constexpr const uint32_t bb_outadr(void){return BITBAND(this->portReg(),this->pos());};

  inline BB_PIN & operator = (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }
  
  inline BB_PIN & operator << (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }

  template<class T> 
  inline BB_PIN & operator >> (T &value){
    value = this->read();
    return *this;
  }

  inline __attribute__((always_inline))
  void write(bool value){MEM_ADDR(this->bb_outadr()) = value;}

  inline __attribute__((always_inline))
  void high(){MEM_ADDR(this->bb_outadr()) = 0x1U;}

  inline __attribute__((always_inline))
  void low(){MEM_ADDR(this->bb_outadr()) = 0x0U;}

  inline operator bool () const __attribute__((always_inline)) {
    return (MEM_ADDR(this->bb_inadr()));
  }

  inline __attribute__((always_inline))
  bool read() const{return MEM_ADDR(this->bb_inadr());}

/*----- comptabled with DigitalPin ----------*/
  inline __attribute__((always_inline))
  void toggle(){write(!MEM_ADDR(this->bb_outadr()));}

  inline __attribute__((always_inline))
  void config(uint8_t mode, bool value) {
	  this->mode(mode);
      this->write(value);
  }

  inline __attribute__((always_inline))
  void mode(uint8_t mode){
	  pinModeLL((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber), mode);}
};

#else
#  define BB_PIN LL_PIN  /*m0/7 use LL_PIN class*/
#endif //BITBAND_OPTION
#pragma GCC diagnostic pop

#endif //__cplusplus
#endif //__BITBAND_H__
