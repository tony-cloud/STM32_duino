#ifndef VARIANT_H
#define VARIANT_H

#define  HAVE_24CXX
#define  HAVE_SPIFLASH
#define  HAVE_SDMMC     
//#define  HAVE_BEEP      PB9
//#define  HAVE_NRF24L01  
//#define  HAVE_DS18B02   PB3
//#define  HAVE_IRREMOTE  PB4
//#define  HAVE_UTFT

#define BOARD_NR_LED            1 
#define LED_BUILTIN             PB0
#define STM32_LED_BUILTIN_ACTIVE_LOW

#define BOARD_NR_KEY        1         
#define BOARD_BUTTON_PIN    PA0

#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA PB7
#define SCL PB6

#endif
