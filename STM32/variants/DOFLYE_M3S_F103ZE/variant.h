#ifndef VARIANT_H
#define VARIANT_H

/************************LED************************/
#define BOARD_NR_LED  2
#define LED_BUILTIN   PB5
#define LED1_BUILTIN  PE5
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BOTTON ************************/
#define BOARD_NR_KEY 4
#define BOTTON	PA0  //1
#define BOTTON1	PE4  //0
#define BOTTON2	PE3  //0
#define BOTTON3	PE2  //0
#define  BOTTON_MASK    0x01
#define KEYS_LIST  BOTTON,BOTTON1,BOTTON2,BOTTON3

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
