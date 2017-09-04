#ifndef VARIANT_H
#define VARIANT_H

/*LED*/
#ifndef LED_BUILTIN
#	define LED_BUILTIN PC13
#endif

#ifndef LED_BUILTIN_MASK
#	define LED_BUILTIN_MASK		0x00
#endif
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*KEY*/
#define KEY_LIST             /*KEY_LIST NUL*/

/*SPI*/
#define MOSI PA7
#define MISO PA6
#define SCK PA5
#define SS PA4

/*I2C*/
#define SDA PB7
#define SCL PB6

/*USB*/
#endif
