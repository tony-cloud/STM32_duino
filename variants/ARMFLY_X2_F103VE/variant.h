#ifndef VARIANT_H
#define VARIANT_H


#define BOARD_NR_LED    2
#define LED_BUILTIN  PC13
#define LED1_BUILTIN PC0
#define LED_BUILTIN_MASK	0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY 8
#define BUTTON	 PA0
#define SYS_WKUP1 			PA0 /*for lowPower*/

#define BUTTON_LEFT	 BUTTON
#define BUTTON1	 PA1
#define BUTTON_UP	 BUTTON1
#define BUTTON2 PC2
#define BUTTON_RIGHT BUTTON2
#define BUTTON3	 PC3
#define BUTTON_DOWN	 BUTTON3
#define BUTTON4	 PC4
#define BUTTON_SEL	 BUTTON4
#define BUTTON5	 PC1
#define BUTTON_KEY1	 BUTTON5
#define BUTTON6	 PE2
#define BUTTON_KEY2	 BUTTON6
#define BUTTON7	 PE3
#define BUTTON_KEY3	 BUTTON7
#define BUTTON_MASK  0x01

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
