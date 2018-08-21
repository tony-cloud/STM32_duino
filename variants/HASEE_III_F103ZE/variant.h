#ifndef VARIANT_H
#define VARIANT_H

//LED USERDEF HASEE_III
#define BOARD_NR_LED  4
#define LED_BUILTIN   PF6
#define LED1_BUILTIN  PF7
#define LED2_BUILTIN  PF8
#define LED3_BUILTIN  PF9
#define LED_BUILTIN_MASK        0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW


/******************** BUTTON ************************/
#define BOARD_NR_KEY 3                
#define BUTTON	PA0
#define SYS_WKUP1	PA0 /*for lowPower*/
#define BUTTON1	PC13
#define BUTTON2	PA8
#define BUTTON3	PD3
#define BUTTON_MASK 0x01

//spi
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

//i2c
#define SDA PB7
#define SCL PB6

//usb
#define USB_DISC_PIN      PG11
#define USB_DISC_LOW      // disconnet by set PG11 set LOW.   add  by huaweiwx@sina.com 2017.4.23

#endif
