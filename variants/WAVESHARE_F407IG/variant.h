#ifndef VARIANT_H
#define VARIANT_H

/*LEDs*/
#define  BOARD_NR_LED 4
#define  LED_BUILTIN  		PH2
#define  LED1_BUILTIN 		PH3
#define  LED2_BUILTIN 		PI8
#define  LED3_BUILTIN 		PI10
#define  LED_BUILTIN_MASK	0x0F
#define STM32_LED_BUILTIN_ACTIVE_HIGH

/*KEYs*/
#define  BOARD_NR_KEY     7
#define  BUTTON           PF10 // USER
#define  BUTTON1 		  PA0  // WAKE
#define  SYS_WKUP1	PA0 /*for lowPower*/
#define  BUTTON2   		  PE6  // CTR
#define  BUTTON3  		  PE5  // D
#define  BUTTON4   		  PE4  // C
#define  BUTTON5   		  PE3  // B
#define  BUTTON6   		  PE2  // A
#define  BUTTON_MASK      0x02

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

#endif
