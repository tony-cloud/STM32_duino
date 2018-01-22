/* 
  huaweiwx@sina.com 2017.  All right reserved.

  for stm32 m3/m4 sram/peripheral bitband io opration
  for all stm32 chips 2017.5.28
  add BB functions from maple 2017.10.12 
  add arduino style class BB_PIN 2017.12.20

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

#if !(defined(STM32F0)||defined(STM32L0)||defined(STM32F7))
//bitband io opration,ʵ��51���Ƶ�GPIO���ƹ���
#define BITBAND(addr, bitnum) (PERIPH_BB_BASE+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO address �ڵ�ַӳ��
#if defined(STM32F1)
	#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
	#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
	#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
	#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
	#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
	#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
	#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

	#define GPIOA_IDR_Addr     (GPIOA_BASE+8) //0x40010808 
	#define GPIOB_IDR_Addr     (GPIOB_BASE+8) //0x40010C08 
	#define GPIOC_IDR_Addr     (GPIOC_BASE+8) //0x40011008 
	#define GPIOD_IDR_Addr     (GPIOD_BASE+8) //0x40011408 
	#define GPIOE_IDR_Addr     (GPIOE_BASE+8) //0x40011808 
	#define GPIOF_IDR_Addr     (GPIOF_BASE+8) //0x40011A08 
	#define GPIOG_IDR_Addr     (GPIOG_BASE+8) //0x40011E08 
	
#elif defined(STM32F2)||defined(STM32F3)||defined(STM32F4)||\
    defined(STM32L1)||defined(STM32L4)
	#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
	#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
	#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
	#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
	#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
	#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
	#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
	#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
	#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

	#define GPIOA_IDR_Addr     (GPIOA_BASE+16) //0x40020010 
	#define GPIOB_IDR_Addr     (GPIOB_BASE+16) //0x40020410 
	#define GPIOC_IDR_Addr     (GPIOC_BASE+16) //0x40020810 
	#define GPIOD_IDR_Addr     (GPIOD_BASE+16) //0x40020C10 
	#define GPIOE_IDR_Addr     (GPIOE_BASE+16) //0x40021010 
	#define GPIOF_IDR_Addr     (GPIOF_BASE+16) //0x40021410 
	#define GPIOG_IDR_Addr     (GPIOG_BASE+16) //0x40021810 
	#define GPIOH_IDR_Addr     (GPIOH_BASE+16) //0x40021C10 
	#define GPIOI_IDR_Addr     (GPIOI_BASE+16) //0x40022010
#endif
  
//n must be less 16!   ȷ��n��ֵС��16!
//example:  in = PAin(0);  
//          PCout(13) = 1;
    
#define PAout(n)   BITBAND_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BITBAND_ADDR(GPIOA_IDR_Addr,n)  //���� 
#define PORTA      GPIOA->ODR    //��� 
#define PINA       GPIOA->IDR    //���� 

#define PBout(n)   BITBAND_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BITBAND_ADDR(GPIOB_IDR_Addr,n)  //���� 
#define PORTB      GPIOB->ODR    //��� 
#define PINB       GPIOB->IDR    //���� 

#define PCout(n)   BITBAND_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BITBAND_ADDR(GPIOC_IDR_Addr,n)  //���� 
#define PORTC      GPIOC->ODR                  //��� 
#define PINC       GPIOC->IDR                  //���� 

#define PDout(n)   BITBAND_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BITBAND_ADDR(GPIOD_IDR_Addr,n)  //���� 
#define PORTD      GPIOD->ODR    //��� 
#define PIND       GPIOD->IDR    //���� 

#define PEout(n)   BITBAND_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BITBAND_ADDR(GPIOE_IDR_Addr,n)  //����
#define PORTE      GPIOE->ODR    //��� 
#define PINE       GPIOE->IDR    //���� 

#define PFout(n)   BITBAND_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BITBAND_ADDR(GPIOF_IDR_Addr,n)  //����
#define PORTF      GPIOF->ODR    //��� 
#define PINF       GPIOF->IDR    //���� 

#define PGout(n)   BITBAND_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BITBAND_ADDR(GPIOG_IDR_Addr,n)  //����
#define PORTG      GPIOG->ODR    //��� 
#define PING       GPIOG->IDR    //���� 

#define PHout(n)   BITBAND_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BITBAND_ADDR(GPIOH_IDR_Addr,n)  //����
#define PORTH      GPIOH->ODR    //��� 
#define PINH       GPIOH->IDR    //���� 

#define PIout(n)   BITBAND_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BITBAND_ADDR(GPIOI_IDR_Addr,n)  //����
#define PORTI      GPIOI->ODR    //��� 
#define PINI       GPIOI->ODR    //���� 

//for arduino const pin add 2017.10
#define PIN_OUTADDR(n)  BITBAND(((uint32_t)&variant_pin_list[n].port->ODR),\
                              BITMASKPOS(variant_pin_list[n].pinMask))
							
#define PIN_INADDR(n)   BITBAND(((uint32_t)&variant_pin_list[n].port->IDR),\
                              BITMASKPOS(variant_pin_list[n].pinMask))
							  
#define PINOut(pin)		MEM_ADDR(PIN_OUTADDR(pin))						
#define PINin(pin)		MEM_ADDR(PIN_OUTADDR(pin))

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
    return (volatile uint32_t*)(bb_base + ((uint32_t)address - bb_ref) * 32 +
                              bit * 4);
}

static inline uint32_t BB_pinAddr(uint32_t pin,uint8_t mode){
	
	uint32_t portaddr =((mode)?((uint32_t) &variant_pin_list[pin].port->ODR)
	                          :((uint32_t) &variant_pin_list[pin].port->IDR));
							  
	uint32_t bit = BITMASKPOS(variant_pin_list[pin].pinMask);
	return BITBAND(portaddr,bit);
}

#ifdef __cplusplus
} // extern "C"

template<const uint8_t PinNumber>
class BB_PIN{
 public:
  //----------------------------------------------------------------------------
  /** Constructor */
  BB_PIN(){};

  inline BB_PIN & operator = (bool value) __attribute__((always_inline)) {
    MEM_ADDR(PIN_OUTADDR(PinNumber)) = value;
    return *this;
  }

   inline operator bool () __attribute__((always_inline)) {
    return (MEM_ADDR(PIN_INADDR(PinNumber)));
  }

  inline __attribute__((always_inline))
  void config(uint8_t mode, bool level) {
	  pinMode(PinNumber,mode);
      MEM_ADDR(PIN_OUTADDR(PinNumber)) = level;
  }

  inline __attribute__((always_inline))
  void high() {
	  MEM_ADDR(PIN_OUTADDR(PinNumber)) = 0x1U;}

  inline __attribute__((always_inline))
  void low() {MEM_ADDR(PIN_OUTADDR(PinNumber)) = 0x0U;}

  inline __attribute__((always_inline))
  void mode(uint8_t mode) {
     pinMode(PinNumber,mode);
  }

  inline __attribute__((always_inline))
  bool read() const {
    return MEM_ADDR(PIN_INADDR(PinNumber));
  }

  inline __attribute__((always_inline))
  void toggle() {
    digitalToggle(PinNumber);
  }

  inline __attribute__((always_inline))
  void write(bool value) {
    MEM_ADDR(PIN_OUTADDR(PinNumber)) = value;
  }
};

#endif //__cplusplus

#else  // L0/F0/F7
 #warning "BitBand unsuport  F0/L0/F7 mcu! use DigitalPin class"
 #include "digitalPin.h"
 #define BB_PIN DigitalPin
#endif // F1/2/3/4 L1/4
#endif //__BITBAND_H__
