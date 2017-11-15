#ifndef VARIANT_H
#define VARIANT_H

#define BOARD_NR_LED          1 
#define LED_BUILTIN PA4
#define LED_BUILTIN_MASK 0
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA  PA10
#define SCL  PA9
#define I2C1_100KHZ_TIMING 0x2000090E

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000800U
#endif
