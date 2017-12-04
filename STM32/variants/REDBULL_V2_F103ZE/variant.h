#ifndef VARIANT_H
#define VARIANT_H

/****************LEDs**************************************/
#define BOARD_NR_LED  5
#define LED_BUILTIN   PF10
#define LED1_BUILTIN  PF9
#define LED2_BUILTIN  PF8
#define LED3_BUILTIN  PF7
#define LED4_BUILTIN  PF6
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BOTTON ********************************/
#define BOARD_NR_KEY 4
#define BOTTON  PA0
#define BOTTON1	PC13
#define BOTTON2	PA8
#define BOTTON3	PD3
#define BOTTON_MASK         0x00
#define KEYS_LIST  BOTTON,BOTTON1,BOTTON2,BOTTON3

/*spi*/
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

/*i2c*/
#define SDA PB7
#define SCL PB6

/*usb*/
#ifndef USB_DISC_PIN 
  #define USB_DISC_PIN      PB5
#endif

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
