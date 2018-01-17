#ifndef VARIANT_H
#define VARIANT_H


#define BOARD_NR_LED    2
#define LED_BUILTIN  PC13
#define LED1_BUILTIN PC0
#define LED_BUILTIN_MASK	0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY 8
#define BOTTON	 PA0
#define BOTTON_LEFT	 BOTTON
#define BOTTON1	 PA1
#define BOTTON_UP	 BOTTON1
#define BOTTON2 PC2
#define BOTTON_RIGHT BOTTON2
#define BOTTON3	 PC3
#define BOTTON_DOWN	 BOTTON3
#define BOTTON4	 PC4
#define BOTTON_SEL	 BOTTON4
#define BOTTON5	 PC1
#define BOTTON_KEY1	 BOTTON5
#define BOTTON6	 PE2
#define BOTTON_KEY2	 BOTTON6
#define BOTTON7	 PE3
#define BOTTON_KEY3	 BOTTON7
#define BOTTON_MASK  0x01

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

#endif
