/* i2cEepromConfig.h  specific board iic eeprom config file

   The definitions can be changed  by  HAL_Conf.h file
*/

#ifndef __BSP_I2CEEPROM_H__
#define __BSP_I2CEEPROM_H__
#include <Arduino.h>


#ifndef  AT24CXX_TYPE
#  ifdef GD32F10X
#    define AT24CXX_TYPE	AT24C02
#  else
#    define AT24CXX_TYPE	AT24C04  //mybard is AT24C04
#  endif
#endif

#ifndef  AT24CXX_DEV
# define AT24CXX_DEV		0	 /*unused i2cport, SOFT IIC only*/
#endif
#ifndef  AT24CXX_SDA
# define AT24CXX_SDA		PC11
#endif
#ifndef  AT24CXX_SCL
# define AT24CXX_SCL		PC12
#endif
#ifndef  AT24CXX_A2A1A0
# define AT24CXX_A2A1A0		0
#endif

#endif   //__BSP_I2CEEPROM_H__