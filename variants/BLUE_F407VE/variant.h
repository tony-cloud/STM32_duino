// board: Black407VE ( STM32F407VE )
// http://wiki.stm32duino.com/images/5/5c/STM32_F4VE_SCHEMATIC.PDF

#ifndef VARIANT_H
#define VARIANT_H

//*************** LED definitions *************************
#define LED_BUILTIN PA6
#define LED1_BUILTIN PA7
#define LED_BUILTIN_MASK   0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

//*************** on board buttons*************************
#define BUTTON	PA0    	/* wakeup, active high*/
#define SYS_WKUP1	PA0 /*for lowPower*/
#define BUTTON1	PE3     /* active low*/
#define BUTTON2 PE4     /* active low*/
#define BUTTON_MASK   0x01

#define USER_BTN KEY_BUTTON  // STM naming compatibility

//*************** SPI pins ********************************
#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

//*************** I2C pins ********************************
#define SDA PB7
#define SCL PB6


#endif
