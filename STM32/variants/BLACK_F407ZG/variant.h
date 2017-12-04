#ifndef VARIANT_H
#define VARIANT_H

/*LED*/
#define LED_BUILTIN  PC0
#define LED_BUILTIN_MASK 0
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*KEY*/

/*SPI*/
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

/*I2C*/
#define SDA PB7
#define SCL PB6

/*USB */
//serial bootloader address
#define SERIAL_LOAD_RAM 0x20003000U

#endif
