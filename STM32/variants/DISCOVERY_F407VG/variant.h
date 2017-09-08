#ifndef VARIANT_H
#define VARIANT_H

//On-board LED pin number           PIN  // Arduino Pin Number         
#define BOARD_NR_LED    4
#define LED_BUILTIN                 PD12 // 18
#define LED_GREEN                   LED_BUILTIN
#define LED1_BUILTIN                PD15 // 18
#define LED_BLUE                    PD15 // 58
#define LED2_BUILTIN                PD14 // 18
#define LED_RED                     PD14 // 19
#define LED3_BUILTIN                PD13 // 18
#define LED_ORANGE                  PD13 // 57
#define LED_BUILTIN_MASK            0x07
#define STM32_LED_BUILTIN_ACTIVE_HIGH

#define LED_RED_OTG_OVERCURRENT     PD5 // be careful with this led. When using it configure the output as PULL_UP.

//On-board user button
#define BOARD_NR_KEY	1
#define BOTTON                    PA0  // 2
#define USER_BTN                  BOTTON  // 2
#define BOTTON_MASK               0X01
#define KEYS_LIST                 BOTTON


// Connected to on board LIS3DSH accelerometer, CS: PE3
#define MOSI                        PA7
#define MISO                        PA6
#define SCK                         PA5
#define SS                          PA4

// Connected to on board CS43L22 audio
#define SDA                         PB9
#define SCL                         PB6

/*USB*/
#endif
