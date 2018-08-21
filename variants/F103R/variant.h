
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H

//led
#define BOARD_NR_LED          1 
#ifndef LED_BUILTIN
 #define LED_BUILTIN PC13
#endif
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*WKUP*/
#define SYS_WKUP1 	PA0 /*for lowPower*/

//SPI
#ifndef MOSI
#define MOSI PA7
#endif
#ifndef MISO
 #define MISO PA6
#endif
#ifndef SCK
 #define SCK  PA5
#endif
#ifndef SS
 #define SS   PA4
#endif

//I2C
#ifndef SDA
 #define SDA PB7
#endif
#ifndef SCL
 #define SCL PB6
#endif

//usb

#endif
