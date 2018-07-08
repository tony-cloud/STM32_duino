#ifndef VARIANT_H
#define VARIANT_H

#define  BOARD_NR_LED 3
#define  LED_BUILTIN  		PB0
#define  LED1_BUILTIN 		PB7
#define  LED2_BUILTIN 		PB14
#define  LED_BUILTIN_MASK	0x07
#define  STM32_LED_BUILTIN_ACTIVE_HIGH

#define  BOARD_NR_KEY        1
#define  BOTTON              PC13 
#define  BOTTON_MASK         0x01
#define  KEYS_LIST  	BOTTON


#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB9
#define SCL PB8

#define I2C1_100KHZ_TIMING 0x20404768
#define I2C2_100KHZ_TIMING 0x20404768
#define I2C3_100KHZ_TIMING 0x20404768
#define I2C4_100KHZ_TIMING 0x20404768


#endif
