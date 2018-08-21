#ifndef VARIANT_H
#define VARIANT_H

//On-board LED pin number           PIN 
#define LED_BUILTIN 				PG13
#define LED_GREEN                   LED_BUILTIN
#define LED1_BUILTIN 				PG14
#define LED_RED                     LED1_BUILTIN 
#define LED_RED_OTG_OVERCURRENT     PC5 // be careful with this led. When using it configure the output as PULL_UP.
#define LED_BUILTIN_MASK            0x03
#define STM32_LED_BUILTIN_ACTIVE_HIGH

//On-board user button
#define BOARD_NR_KEY 1
#define BUTTON   PA0
#define SYS_WKUP1 			PA0 /*for lowPower*/
#define USER_BTN BUTTON 
#define BUTTON_MASK         0x01

// Connected to on board LIS3DSH accelerometer, CS: PE3
#define MOSI PA7
#define MISO PA6
#define SCK PA5
#define SS PA4

// Connected to on board CS43L22 audio
#define SDA PB9
#define SCL PB6


#endif
