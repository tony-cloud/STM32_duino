#ifndef VARIANT_H
#define VARIANT_H

//led
#define BOARD_NR_LED          1 
#define LED_BUILTIN PC13
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

//SPI
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

//I2C
#define SDA PB7
#define SCL PB6

//usb

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
