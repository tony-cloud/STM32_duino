#ifndef VARIANT_H
#define VARIANT_H

/************************LED************************/
#define BOARD_NR_LED  2
#define LED_BUILTIN   PD13
#define LED1_BUILTIN  PG14
#define LED_BUILTIN_MASK		0x03
//#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BOTTON ************************/
#define BOARD_NR_KEY 2
#define BOTTON	PE0   //0
#define BOTTON1	PC13  //0
#define BOTTON_MASK    0x0
#define KEYS_LIST  BOTTON,BOTTON1

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
