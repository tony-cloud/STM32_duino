#ifndef VARIANT_H
#define VARIANT_H

/******************** LED ************************/
#define BOARD_NR_LED            3 
#define LED_BUILTIN  			PE3
#define LED1_BUILTIN 			PE4
#define LED2_BUILTIN 			PG9
#define LED_BUILTIN_MASK		0x00
#define STM32_LED_BUILTIN_ACTIVE_LOW

/******************** BUTTON ************************/
#define  BOARD_NR_KEY		4                     
#define  BUTTON		PF9     /* K0/S3 */
#define  BUTTON1	PF8     /* K1/S2 */
#define  BUTTON2	PF7     /* K2/S1 */
#define  BUTTON3	PF6     /* K3/S0 */
#define  BUTTON_MASK         0x00
/*WKUP*/
#define SYS_WKUP1 	PA0 /*for lowPower*/


#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB9
#define SCL PB8

#endif
