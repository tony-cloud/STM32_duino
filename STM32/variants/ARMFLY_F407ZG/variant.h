#ifndef VARIANT_H
#define VARIANT_H

#define BOARD_NR_LED          2 
#define LED_BUILTIN  			PG7
#define LED1_BUILTIN 			PG8
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY        1
#define BOTTON              PA0
#define BOTTON_MASK         0x01
#define KEYS_LIST           BOTTON
  

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SCL PB6
#define SDA PB7

//serial bootloader address
#define SERIAL_LOAD_RAM 0x20003000U

#endif
