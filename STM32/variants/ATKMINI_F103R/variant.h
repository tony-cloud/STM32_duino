#ifndef VARIANT_H
#define VARIANT_H

//led  
#define BOARD_NR_LED              2
#define LED_BUILTIN              PD2   //!!需改成目标板子上的具体led 位置!!
#define LED1_BUILTIN             PA8   //!!需改成目标板子上的具体led 位置!!
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

//key
#define BOARD_NR_KEY              3
#define  BOTTON              PA0
#define  BOTTON1             PA13    //!!需改成目标板子上的具体KEY 位置!!
#define  BOTTON2             PA15    //!!需改成目标板子上的具体KEY 位置!!   
#define  BOTTON_MASK         0x01
#define  KEYS_LIST  BOTTON,BOTTON1,BOTTON2

//spi
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

//i2c
#define SDA PB7
#define SCL PB6

//usb disconnected

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
