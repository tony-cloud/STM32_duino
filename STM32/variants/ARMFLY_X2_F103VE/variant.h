#ifndef VARIANT_H
#define VARIANT_H


#define BOARD_NR_LED    2
#define LED_BUILTIN  PC13
#define LED1_BUILTIN PC0
#define LED_BUILTIN_MASK	0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY 8
#define BOTTON_LEFT	 PA0
#define BOTTON_UP	 PA1
#define BOTTON_RIGHT PC2
#define BOTTON_DOWN	 PC3
#define BOTTON_SEL	 PC4
#define BOTTON_KEY1	 PC1
#define BOTTON_KEY2	 PE2
#define BOTTON_KEY3	 PE3
#define BOTTON_MASK  0x01
#define KEYS_LIST  BOTTON_LEFT,BOTTON_UP,BOTTON_RIGHT,BOTTON_DOWN,BOTTON_SEL,BOTTON_KEY1,BOTTON_KEY2,BOTTON_KEY3

/******************** SPI ************************/
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

/******************** I2C ************************/
#define SDA PB7
#define SCL PB6

/******************** USB DIC ************************/
#ifndef USB_DISC_PIN
  #define USB_DISC_PIN      PE1  //103Zet6 is PB14
#endif

//serial bootloader address
# define SERIAL_LOAD_RAM 0x20000200U

#endif
