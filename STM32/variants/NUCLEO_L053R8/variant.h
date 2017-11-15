#ifndef VARIANT_H
#define VARIANT_H


//LED
#define BOARD_NR_LED    1
#define LED_BUILTIN PA5
#define LED_BUILTIN_MASK 1
#define STM32_LED_BUILTIN_ACTIVE_HIGH

//On-board user button
#define BOARD_NR_KEY	1
#define BOTTON			PC13  // 2
#define USER_BTN		BOTTON  // 2
#define BOTTON_MASK		0x00
#define KEYS_LIST       BOTTON

#define MOSI PA7
#define MISO PA6
#define SCK PA5
#define SS PA4

#define SDA PB9
#define SCL PB8
#define I2C1_100KHZ_TIMING 0x00000708
#define I2C2_100KHZ_TIMING 0x00000708
#define I2C3_100KHZ_TIMING 0x00000708

#define A0 PA0
#define A1 PA1
#define A2 PA4
#define A3 PB0
#define A4 PC1
#define A5 PC0

#define VARIANT_PIN_LIST \
   PIN(A,3 ), /* D0 */ \
   PIN(A,2 ), /* D1 */ \
   PIN(A,10), /* D2 */ \
   PIN(B,3 ), /* D3 */ \
   PIN(B,5 ), /* D4 */ \
   PIN(B,4 ), /* D5 */ \
   PIN(B,10), /* D6 */ \
   PIN(A,8 ), /* D7 */ \
   PIN(A,9 ), /* D8 */ \
   PIN(C,7 ), /* D9 */ \
   PIN(B,6 ), /* D10 */ \
   PIN(A,7 ), /* D11 */ \
   PIN(A,6 ), /* D12 */ \
   PIN(A,5 ), /* D13 */ \
   PIN(B,9 ), /* D14 */ \
   PIN(B,8 ), /* D15 */ \
   PIN(A,0 ), /* D16 / A0 */ \
   PIN(A,1 ), /* D17 / A1 */ \
   PIN(A,4 ), /* D18 / A2 */ \
   PIN(B,0 ), /* D19 / A3 */ \
   PIN(C,1 ), /* D20 / A4 */ \
   PIN(C,0 ), /* D21 / A5 */ \
   PIN(A,11), \
   PIN(A,12), \
   PIN(A,13), \
   PIN(A,14), \
   PIN(A,15), \
   PIN(B,1 ), \
   PIN(B,2 ), \
   PIN(B,7 ), \
   PIN(B,12), \
   PIN(B,13), \
   PIN(B,14), \
   PIN(B,15), \
   PIN(C,2 ), \
   PIN(C,3 ), \
   PIN(C,4 ), \
   PIN(C,5 ), \
   PIN(C,6 ), \
   PIN(C,8 ), \
   PIN(C,9 ), \
   PIN(C,10), \
   PIN(C,11), \
   PIN(C,12), \
   PIN(C,13), \
   PIN(C,14), \
   PIN(C,15), \
   PIN(D,2 ),

#endif
