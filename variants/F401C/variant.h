
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H

/*LED*/
#define BOARD_NR_LED          1 
#ifndef LED_BUILTIN
 #define LED_BUILTIN PC13 
#endif

#ifndef LED_BUILTIN_MASK
 #define LED_BUILTIN_MASK		0x00
#endif
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*KEYS*/
/*WKUP*/
#define SYS_WKUP1 	PA0 /*for lowPower*/

/*SPI*/
#ifndef MOSI
 #define MOSI PA7
#endif
#ifndef MISO
 #define MISO PA6
#endif
#ifndef SCK
 #define SCK PA5
#endif
#ifndef SS
 #define SS PA4
#endif

/*I2C*/
#ifndef SDA
 #define SDA PB8
#endif
#ifndef SCL
 #define SCL PB9
#endif

#define A0 PA0
#define A1 PA1
#define A2 PA4
#define A3 PB0

#endif

