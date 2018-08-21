
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H

#define BOARD_NR_LED  1 
#ifndef LED_BUILTIN
 #define LED_BUILTIN PA4
#endif
#define LED_BUILTIN_MASK 0
#define STM32_LED_BUILTIN_ACTIVE_LOW

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

#ifndef SDA
 #define SDA  PA10
#endif
#ifndef SCL
 #define SCL  PA9
#endif

#define I2C1_100KHZ_TIMING 0x2000090E

#endif
