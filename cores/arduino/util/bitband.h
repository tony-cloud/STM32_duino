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

/* 
m0 m7 have not bitband
STM32F3/STM32L4 GPIO unsupport bitband opration 
*/
#if defined(STM32F0)||defined(STM32L0)||defined(STM32F7)||defined(STM32H7)||defined(STM32F3)||defined(STM32L4)
#	define BITBAND_OPTION 0
#else
#	define BITBAND_OPTION 1 
#endif

#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 

/*compatable with avr*/
#ifdef GPIOA
# define PORTA      GPIOA->ODR    //输出 
# define PINA       GPIOA->IDR    //输入
#endif
#ifdef GPIOB
# define PORTB      GPIOB->ODR    //输出 
# define PINB       GPIOB->IDR    //输入 
#endif
#ifdef GPIOC
# define PORTC      GPIOC->ODR                  //输出 
# define PINC       GPIOC->IDR                  //输入 
#endif
#ifdef GPIOD
# define PORTD      GPIOD->ODR    //输出 
# define PIND       GPIOD->IDR    //输入 
#endif
#ifdef GPIOE
# define PORTE      GPIOE->ODR    //输出 
# define PINE       GPIOE->IDR    //输入 
#endif
#ifdef GPIOF
# define PORTF      GPIOF->ODR    //输出 
# define PINF       GPIOF->IDR    //输入 
#endif
#ifdef GPIOG
# define PORTG      GPIOG->ODR    //输出 
# define PING       GPIOG->IDR    //输入 
#endif
#ifdef GPIOH
# define PORTH      GPIOH->ODR    //输出 
# define PINH       GPIOH->IDR    //输入 
#endif
#ifdef GPIOI
# define PORTI      GPIOI->ODR    //输出 
# define PINI       GPIOI->IDR    //输入 
#endif

#if BITBAND_OPTION
//bitband io opration,实现51类似的GPIO控制功能
#define BITBAND(addr, bitnum) (PERIPH_BB_BASE+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//n must be less 16!   确保n的值小于16!
//example:  in = PAin(0);  
//          PCout(13) = 1;
#ifdef GPIOA
# define PAout(n)   BITBAND_ADDR((uint32_t)&PORTA,n)  //输出 
# define PAin(n)    BITBAND_ADDR((uint32_t)&PINA,n)   //输入 
#endif
#ifdef GPIOB
# define PBout(n)   BITBAND_ADDR((uint32_t)&PORTB,n)  //输出 
# define PBin(n)    BITBAND_ADDR((uint32_t)&PINB,n)   //输入 
#endif
#ifdef GPIOC
# define PCout(n)   BITBAND_ADDR((uint32_t)&PORTC,n)  //输出 
# define PCin(n)    BITBAND_ADDR((uint32_t)&PINC,n)   //输入 
#endif
#ifdef GPIOD
# define PDout(n)   BITBAND_ADDR((uint32_t)&PORTD,n)  //输出 
# define PDin(n)    BITBAND_ADDR((uint32_t)&PIND,n)   //输入 
#endif
#ifdef GPIOE
# define PEout(n)   BITBAND_ADDR((uint32_t)&PORTE,n)  //输出 
# define PEin(n)    BITBAND_ADDR((uint32_t)&PINE,n)   //输入
#endif
#ifdef GPIOF
# define PFout(n)   BITBAND_ADDR((uint32_t)&PORTF,n)  //输出 
# define PFin(n)    BITBAND_ADDR((uint32_t)&PINF,n)   //输入
#endif
#ifdef GPIOG
# define PGout(n)   BITBAND_ADDR((uint32_t)&PORTG,n)  //输出 
# define PGin(n)    BITBAND_ADDR((uint32_t)&PING,n)   //输入
#endif
#ifdef GPIOH
# define PHout(n)   BITBAND_ADDR((uint32_t)&PORTH,n)  //输出 
# define PHin(n)    BITBAND_ADDR((uint32_t)&PINH,n)   //输入
#endif
#ifdef GPIOI
# define PIout(n)   BITBAND_ADDR((uint32_t)&PORTI,n)  //输出 
# define PIin(n)    BITBAND_ADDR((uint32_t)&PINI,n)   //输入
#endif

//for arduino pin add 2017.10
#ifdef VARIANT_PIN_LIST
# define PIN_OUTADR(pin) BITBAND(((const uint32_t)&variant_pin_list[pin].port->ODR),BITMASKPOS(variant_pin_list[pin].pinMask))
# define PIN_INADR(pin)  BITBAND(((const uint32_t)&variant_pin_list[pin].port->IDR),BITMASKPOS(variant_pin_list[pin].pinMask))
# define PINout(pin)	MEM_ADDR(PIN_OUTADR(pin))						
# define PINin(pin)	MEM_ADDR(PIN_OUTADR(pin))

#else /*CHIP_PIN_LIST */
# ifdef STM32F1
#    define PIN_OUTADR(pin) BITBAND((GPIOA_BASE+(((pin)>>4)&0x0f)*(GPIOB_BASE-GPIOA_BASE)+12),((pin)&0x0f))
#    define PIN_INADR(pin)  BITBAND((GPIOA_BASE+(((pin)>>4)&0x0f)*(GPIOB_BASE-GPIOA_BASE)+ 8),((pin)&0x0f))
# else
#    define PIN_OUTADR(pin) BITBAND((GPIOA_BASE+(((pin)>>4)&0x0f)*(GPIOB_BASE-GPIOA_BASE)+20),((pin)&0x0f))
#    define PIN_INADR(pin)  BITBAND((GPIOA_BASE+(((pin)>>4)&0x0f)*(GPIOB_BASE-GPIOA_BASE)+16),((pin)&0x0f))
# endif /*STM32F1*/

# ifdef __cplusplus  /*for __ConstPin*/
#   ifdef STM32F1
#     define PINout(pin)	BITBAND_ADDR((pinToBase(pin)+12),	pinMaskPos(pin))			
#     define PINin(pin)		BITBAND_ADDR((pinToBase(pin)+8) ,	pinMaskPos(pin))
#   else
#     define PINout(pin)	BITBAND_ADDR((pinToBase(pin)+20),	pinMaskPos(pin))			
#     define PINin(pin)		BITBAND_ADDR((pinToBase(pin)+16),	pinMaskPos(pin))
#   endif
# else
#  define PINout(pin)	MEM_ADDR(PIN_OUTADR(pin))						
#  define PINin(pin)	MEM_ADDR(PIN_OUTADR(pin))
# endif /*__cplusplus*/
#endif /*VARIANT_PIN_LIST*/

#define BB_sramVarPtr(x)  __BB_addr((volatile uint32_t*)&(x), 0, SRAM_BB_BASE, SRAM_BASE)

#ifdef __cplusplus
extern "C" {
#endif
static inline volatile uint32_t* __BB_addr(volatile void*,uint32_t,uint32_t,uint32_t);

/**
 * @brief Obtain a pointer to the bit-band address corresponding to a
 *        bit in a volatile SRAM address.
 * @param address Address in the bit-banded SRAM region
 * @param bit     Bit in address to bit-band
 */
static inline volatile uint32_t* BB_sramp(volatile void *address, uint32_t bit){
    return __BB_addr(address, bit, SRAM_BB_BASE, SRAM_BASE);
}

/**
 * @brief Get a bit from an address in the SRAM bit-band region.
 * @param address Address in the SRAM bit-band region to read from
 * @param bit Bit in address to read
 * @return bit's value in address.
 */
static inline uint8_t BB_sramGetBit(volatile void *address, uint32_t bit){
    return *BB_sramp(address, bit);
}

/**
 * @brief Set a bit in an address in the SRAM bit-band region.
 * @param address Address in the SRAM bit-band region to write to
 * @param bit Bit in address to write to
 * @param val Value to write for bit, either 0 or 1.
 */
static inline void BB_sramSetBit(volatile void *address,uint32_t bit,uint8_t val){
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
static inline void BB_periSetBit(volatile void *address,uint32_t bit,uint8_t val) {
    *BB_perip(address, bit) = val;
}

static inline volatile uint32_t* __BB_addr(volatile void *address,uint32_t bit,uint32_t bb_base,uint32_t bb_ref) {
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
  constexpr const uint32_t pinMask(void){return (uint32_t)(1<<(this->pos()));};
  constexpr GPIO_TypeDef* port(void){return (GPIO_TypeDef *)(this->base());};
  
  inline LL_PIN & operator = (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }
  
  inline LL_PIN & operator << (bool value) __attribute__((always_inline)) {
    this->write(value);
    return *this;
  }
  
  inline LL_PIN & operator << (int value) __attribute__((always_inline)) {
    this->write((bool)value);
    return *this;
  }

  template<class T> 
  inline LL_PIN & operator >> (T &value){
    value = this->read();
    return *this;
  }

  inline __attribute__((always_inline))
  void write(bool value){
#ifdef STM32H7
//    HAL_GPIO_WritePin((GPIO_TypeDef *)(this->base()),this->pinMask(),(GPIO_PinState)value);
    if(value != GPIO_PIN_RESET)
    {
      ((GPIO_TypeDef *)(this->base()))->BSRRL = this->pinMask();
    }else{
      ((GPIO_TypeDef *)(this->base()))->BSRRH = this->pinMask() ;
    }
#else	
    if (value) {
        LL_GPIO_SetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
    } else {
        LL_GPIO_ResetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
    }
#endif
  }

  inline __attribute__((always_inline))
  void high(){
#ifdef STM32H7
    ((GPIO_TypeDef *)(this->base()))->BSRRL = this->pinMask();
#else		  
	LL_GPIO_SetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
#endif  
  }

  inline __attribute__((always_inline))
  void low(){
#ifdef STM32H7
     ((GPIO_TypeDef *)(this->base()))->BSRRH = this->pinMask() ;
#else		  
	 LL_GPIO_ResetOutputPin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
#endif
  }

  inline operator bool () const __attribute__((always_inline)) {
    return this->read();
  }

  inline __attribute__((always_inline))
  bool read() const{
#ifdef STM32H7
    return HAL_GPIO_ReadPin((GPIO_TypeDef *)(this->base()),this->pinMask());
#else	 
	return LL_GPIO_IsInputPinSet((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
#endif
  }

  inline void operator  !() __attribute__((always_inline)) {
    this->toggle();
  }

/*----- comptabled with DigitalPin ----------*/
  inline __attribute__((always_inline))
  void toggle(){
#ifdef STM32H7
    ((GPIO_TypeDef *)(this->base()))->ODR ^= this->pinMask() ;
#else
	LL_GPIO_TogglePin((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber));
#endif  
  }
  
  inline __attribute__((always_inline))
  void config(uint8_t mode, bool level) {  /*compatale with digitalPin*/
	  this->mode(mode);
      this->write(level);
  }

  inline __attribute__((always_inline))
  void mode(uint8_t mode){
#ifdef STM32H7
    pinMode(PinNumber,mode);
#else 
	pinModeLL((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber), mode);
#endif
  }

  inline __attribute__((always_inline))
  void attach(voidFuncPtr callback, uint8_t mode){
	  attachInterrupt(PinNumber, callback, mode);
  }
  
  inline __attribute__((always_inline))
  void detach(void){
	  detachInterrupt(PinNumber);
  }

};

#if BITBAND_OPTION
template<const int PinNumber>
class BB_PIN{
 public:
  //----------------------------------------------------------------------------
  constexpr const uint8_t  pos(void){return variant_gpiopin_pos_static[PinNumber];};
  constexpr const uint32_t base(void){return variant_gpiopin_base_static[PinNumber];};
  constexpr const uint32_t pinMask(void){return (uint32_t)(1<<(this->pos()));};

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
  
  inline BB_PIN & operator << (int value) __attribute__((always_inline)) {
    this->write((bool)value);
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

  inline void operator  !() __attribute__((always_inline)) {
    this->toggle();
  }

/*----- comptabled with DigitalPin ----------*/
  inline __attribute__((always_inline))
  void toggle(){write(!MEM_ADDR(this->bb_outadr()));}

  inline __attribute__((always_inline))
  void config(uint8_t mode, bool value) {  /*compatale with digitalPin*/
	  this->mode(mode);
      this->write(value);
  }

  inline __attribute__((always_inline))
  void mode(uint8_t mode){
	  pinModeLL((GPIO_TypeDef *)(this->base()), pinTollBitMask(PinNumber), mode);}
	  
  inline __attribute__((always_inline))
  void attach(voidFuncPtr callback, uint8_t mode){
	  attachInterrupt(PinNumber, callback, mode);
  }
  
  inline __attribute__((always_inline))
  void detach(void){
	  detachInterrupt(PinNumber);
  }

};

#else
#  define BB_PIN LL_PIN  /*m0/7 use LL_PIN class*/
#endif //BITBAND_OPTION
#pragma GCC diagnostic pop

#define FAST_PIN BB_PIN

#if BITBAND_OPTION
template<class T> 
class BB_VAR{
  public:	
	T val;
    inline  operator T() __attribute__((always_inline)) { return this->val;};
	inline  BB_VAR& operator = (T value) __attribute__((always_inline)){
		this->val =value; 
		return *this;
	};
	volatile  uint32_t* pos = BB_sramVarPtr(val);
};
#endif

#endif //__cplusplus
#endif //__BITBAND_H__
