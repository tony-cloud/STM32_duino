
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H


/******************** LED ************************/
#define BOARD_NR_LED        2
#ifndef LED_BUILTIN
 #define LED_BUILTIN         PA6
#endif
#ifndef LED1_BUILTIN
 #define LED1_BUILTIN        PA7
#endif
#ifndef LED_BUILTIN_MASK
 #define LED_BUILTIN_MASK	0
#endif
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BUTTON **********************/
#define BOARD_NR_KEY 3
#ifndef BUTTON
 #define BUTTON	PA0
 #define SYS_WKUP1	PA0 /*for lowPower*/
#endif
#ifndef BUTTON1
 #define BUTTON1	PE3
#endif
#ifndef BUTTON2
 #define BUTTON2	PE4
#endif
#ifndef BUTTON_MASK
 #define BUTTON_MASK	0x01
#endif

/******************** SPI ************************/
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

/******************** I2C ************************/
#ifndef SDA
 #define SDA PB7
#endif
#ifndef SCL
 #define SCL PB6
#endif

#endif /*VARIANT_H*/
