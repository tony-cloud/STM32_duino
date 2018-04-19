/* i2ceepromconfig.h  specific board iic_eeprom config file ,arduino have not autoload! */
#ifndef __I2CEEPROMCONFIG_H__
#define __I2CEEPROMCONFIG_H__


#ifdef GD32F10X
#define AT24CXX_TYPE AT24C02
#else
#define AT24CXX_TYPE AT24C04  //mybard is AT24C04
#endif
	
#define AT24CXX_DEV	 0	/*unused i2cport ,SOFT IIC*/
#define AT24CXX_SDA PC11
#define AT24CXX_SCL PC12
#define AT24CXX_A2A1A0    0

#endif   //__BSP_I2CEEPROM_H__