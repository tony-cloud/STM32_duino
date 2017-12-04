#ifndef VARIANT_H
#define VARIANT_H


/******************** LED ************************/
#define BOARD_NR_LED        2 
#define LED_BUILTIN         PA6
#define LED1_BUILTIN        PA7
#define LED_BUILTIN_MASK	0
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BOTTON ************************/
#define BOARD_NR_KEY 3
#define BOTTON	PA0
#define BOTTON1	PE3
#define BOTTON2	PE4
#define BOTTON_MASK	0x01
#define KEYS_LIST  BOTTON,BOTTON1,BOTTON2

//SPI
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

//I2C
#define SDA PB7
#define SCL PB6

//serial bootloader address
#define SERIAL_LOAD_RAM 0x20003000U

#endif
