#ifndef VARIANT_H
#define VARIANT_H
#define  HAVE_24CXX
#define  HAVE_485
#define  HAVE_BEEP
#define  HAVE_CAN
//#define  HAVE_DS18B02
#define  HAVE_EXTSRAM
//#define  HAVE_IRREMOTE
//#define  HAVE_LDR
//#define  HAVE_NAND
//#define  HAVE_NOR
//#define  HAVE_NRF24L01
//#define  HAVE_OLED
//#define  HAVE_PS2
#define  HAVE_SPIFLASH SPI1
#define  HAVE_SDMMC

//LED USERDEF RedBull
#define BOARD_NR_LED  5
#define LED_BUILTIN   PF6
#define LED1_BUILTIN  PF7
#define LED2_BUILTIN  PF8
#define LED3_BUILTIN  PF9
#define LED4_BUILTIN  PF10
#define  LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

//BOTTON DEF

#define BOARD_NR_KEY         4
#define BOTTON          PA0
#define BOTTON1         PC13    //!!需改成目标板子上的具体KEY 位置!!
#define BOTTON2         PA8    //!!需改成目标板子上的具体KEY 位置!!   
#define BOTTON3         PD3    //!!需改成目标板子上的具体KEY 位置!!   
#define BOTTON_MASK     0x00
  
#define BEEP_BUILTIN             PB10

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

#endif
