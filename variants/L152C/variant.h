
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H

/*LED*/
#define BOARD_NR_LED   1 
#ifndef LED_BUILTIN
 #define LED_BUILTIN PB9
#endif

#ifndef LED_BUILTIN_MASK
 #define LED_BUILTIN_MASK		0x00
#endif
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*KEY*/
#define BOARD_NR_KEY	1
#ifndef BUTTON
 #define BUTTON			PC13  // 2
#endif
#ifndef BUTTON_MASK
 #define BUTTON_MASK		0x01
#endif

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
/*USB*/

#endif
