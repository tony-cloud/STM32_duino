//for stm32 gpio bitband io opration
//2017.5.28 for all stm32 chips
//modify by huawei<huaweiwx@sina.com> 2016.9.18

#ifndef __LIKE51_H__
#define __LIKE51_H__

//bitband io opration,实现51类似的GPIO控制功能
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO address 口地址映射
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
	
#elif defined(STM32F0)||defined(STM32F2)||defined(STM32F3)||defined(STM32F4)||defined(STM32F7)||\
    defined(STM32L0)||defined(STM32L1)||defined(STM32L4)
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
#else
	#error  "for STM32F1/F4/F7"	
#endif
  
//n must be less 16!   确保n的值小于16!
//example:  in = PAin(0);  
//          PCout(13) = 1;
    
#define PAout(n)   BITBAND_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BITBAND_ADDR(GPIOA_IDR_Addr,n)  //输入 
#define PORTA      GPIOA->ODR    //输出 
#define PINA       GPIOA->IDR    //输入 

#define PBout(n)   BITBAND_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BITBAND_ADDR(GPIOB_IDR_Addr,n)  //输入 
#define PORTB      GPIOB->ODR    //输出 
#define PINB       GPIOB->IDR    //输入 

#define PCout(n)   BITBAND_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BITBAND_ADDR(GPIOC_IDR_Addr,n)  //输入 
#define PORTC      GPIOC->ODR                  //输出 
#define PINC       GPIOC->IDR                  //输入 

#define PDout(n)   BITBAND_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BITBAND_ADDR(GPIOD_IDR_Addr,n)  //输入 
#define PORTD      GPIOD->ODR    //输出 
#define PIND       GPIOD->IDR    //输入 

#define PEout(n)   BITBAND_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BITBAND_ADDR(GPIOE_IDR_Addr,n)  //输入
#define PORTE      GPIOE->ODR    //输出 
#define PINE       GPIOE->IDR    //输入 

#define PFout(n)   BITBAND_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BITBAND_ADDR(GPIOF_IDR_Addr,n)  //输入
#define PORTF      GPIOF->ODR    //输出 
#define PINF       GPIOF->IDR    //输入 

#define PGout(n)   BITBAND_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BITBAND_ADDR(GPIOG_IDR_Addr,n)  //输入
#define PORTG      GPIOG->ODR    //输出 
#define PING       GPIOG->IDR    //输入 

#define PHout(n)   BITBAND_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BITBAND_ADDR(GPIOH_IDR_Addr,n)  //输入
#define PORTH      GPIOH->ODR    //输出 
#define PINH       GPIOH->IDR    //输入 

#define PIout(n)   BITBAND_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BITBAND_ADDR(GPIOI_IDR_Addr,n)  //输入
#define PORTI      GPIOI->ODR    //输出 
#define PINI       GPIOI->ODR    //输入 

#endif











