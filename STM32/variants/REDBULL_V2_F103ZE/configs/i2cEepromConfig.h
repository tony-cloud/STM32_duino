/* i2cEepromConfig.h: The specific board iiceeprom configfile ,arduino have not autoload! */
#ifndef __BSP_I2CEEPROM_H__
#define __BSP_I2CEEPROM_H__
//#include <Arduino.h>

//#define AT24CXX_TYPE AT24C02  /*standard board use 24c02*/
#define AT24CXX_TYPE AT24C512   /*my diy board use 24c512*/
#define AT24CXX_IIC_DEV	I2C1 	    /*unused i2cport ,SOFT IIC*/
#define AT24CXX_SCL PB6
#define AT24CXX_SDA PB7
#define AT24CXX_A2A1A0 0x00        /* AT24Cxx A2/A1/A0 LOW*/

#endif   //__BSP_I2CEEPROM_H__