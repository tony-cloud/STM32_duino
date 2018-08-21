#ifndef VARIANT_H
#define VARIANT_H

//On-board LED pin number           PIN  // Arduino Pin Number         
#define BOARD_NR_LED            8
#define LED_BUILTIN             PE8
#define LED1_BUILTIN            PE9
#define LED2_BUILTIN            PE10
#define LED3_BUILTIN            PE11
#define LED4_BUILTIN            PE12
#define LED5_BUILTIN            PE13
#define LED6_BUILTIN            PE14
#define LED7_BUILTIN            PE15
#define LED_BUILTIN_MASK        0xFF   //ON 1
#define STM32_LED_BUILTIN_ACTIVE_HIGH

#define BOARD_NR_KEY       1
#define BUTTON             PA0
#define SYS_WKUP1		   PA0 /*for lowPower*/
#define BUTTON_MASK        0x01    //PRESED 1

//On-board user button
#define USER_BTN                  PA0  // 2


// Connected to on board LIS3DSH accelerometer, CS: PE3
#define MOSI                        PA7
#define MISO                        PA6
#define SCK                         PA5
#define SS                          PA4

// Connected to on board CS43L22 audio
#define SDA                         PB9
#define SCL                         PB6

#define I2C1_100KHZ_TIMING 0x2000090E
#define I2C2_100KHZ_TIMING 0x2000090E
#define I2C3_100KHZ_TIMING 0x2000090E
#define I2C4_100KHZ_TIMING 0x2000090E

//USB

#endif
