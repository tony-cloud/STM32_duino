#ifndef VARIANT_H
#define VARIANT_H

#define LED_BUILTIN PA5
#define LED_BUILTIN_MASK 1
#define STM32_LED_BUILTIN_ACTIVE_HIGH

#define BUTTON			PA0  // 2
#define BUTTON_MASK		0x01
#define SYS_WKUP1 	 PA0 /*for lowPower*/

#define MOSI PB5
#define MISO PB4
#define SCK PB3
#define SS PA4

#define SDA PB9
#define SCL PB8
#define I2C1_100KHZ_TIMING 0x00000708
#define I2C2_100KHZ_TIMING 0x00000708
#define I2C3_100KHZ_TIMING 0x00000708


#endif
