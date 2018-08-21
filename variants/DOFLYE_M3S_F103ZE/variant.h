#ifndef VARIANT_H
#define VARIANT_H

/************************LED************************/
#define BOARD_NR_LED  2
#define LED_BUILTIN   PB5
#define LED1_BUILTIN  PE5
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BUTTON ************************/
#define BOARD_NR_KEY 4
#define BUTTON	PA0  //1
#define SYS_WKUP1	PA0 /*for lowPower*/
#define BUTTON1	PE4  //0
#define BUTTON2	PE3  //0
#define BUTTON3	PE2  //0
#define BUTTON_MASK    0x01

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

#endif
