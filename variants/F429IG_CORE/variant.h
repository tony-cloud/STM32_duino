#ifndef VARIANT_H
#define VARIANT_H

#define BOARD_NR_LED        1 
#define LED_BUILTIN         PB0
#define LED_BUILTIN_MASK	0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY        1         
#define BUTTON          PA0
#define SYS_WKUP1	PA0 /*for lowPower*/
#define BUTTON_MASK         0x01

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

#endif
