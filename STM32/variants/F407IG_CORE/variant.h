#ifndef VARIANT_H
#define VARIANT_H

#define BOARD_NR_LED            1 
#define LED_BUILTIN             PB0
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY        1         
#define BOARD_BUTTON_PIN    PA0
#define BOTTON_MASK         0x01
#define KEYS_LIST           BOTTON

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

//serial bootloader address
#define SERIAL_LOAD_RAM 0x20003000U

#endif
