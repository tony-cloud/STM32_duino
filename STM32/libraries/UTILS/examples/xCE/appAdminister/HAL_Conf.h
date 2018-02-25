/*   ARDUINO HAL special config file, overriden default define 
 *   use this config file for save space 
 *   config arduino/hal/os/priority/......
 *   ARDUINO HAL 项目配置文件， 改写 系统、库、缺省定义，配置改变系统的缺省参数/中断优先级等,节约内存；
 *   !!! Don't rename this file, 请不要改变文件名和扩展名!!!
 *    2017.12 by huawei
 */
 
#ifndef __HALSPECELCONFIG_H__
#define __HALSPECELCONFIG_H__

/*USE_SERIALx default 1*/
#if defined(ARDUINO_NUCLEO_F303RE)||defined(ARDUINO_NUCLEO_F401RE)||defined(ARDUINO_NUCLEO_F411RE)||\
    defined(ARDUINO_NUCLEO_L476RG)||defined(ARDUINO_NUCLEO_F207ZG)||defined(ARDUINO_NUCLEO_F767ZI)||\
    defined(ARDUINO_DISCOVERY_F303VC)
#ifndef USE_SERIAL1
#define USE_SERIAL1 0  /*0 unused serial2 save space*/
#endif
#else
#ifndef USE_SERIAL1
#define USE_SERIAL1 1
#endif
#endif

#if defined(ARDUINO_NUCLEO_F303RE)||defined(ARDUINO_NUCLEO_F401RE)||defined(ARDUINO_NUCLEO_F411RE)||defined(ARDUINO_NUCLEO_L476RG)||\
    defined(ARDUINO_DISCOVERY_F303VC)
#ifndef USE_SERIAL2
#define USE_SERIAL2 1
#endif
#else
#ifndef USE_SERIAL2
#define USE_SERIAL2 0  /*0 unused serial2 save space*/
#endif
#endif

#if defined(ARDUINO_NUCLEO_F207ZG)||defined(ARDUINO_NUCLEO_F767ZI)
#ifndef USE_SERIAL3
#define USE_SERIAL3 1
#endif
#else
#ifndef USE_SERIAL3
#define USE_SERIAL3 0 /*0 unused serial3 save space*/
#endif
#endif

#ifndef USE_SERIAL4
#define USE_SERIAL4 0/*0 unused serial4 save space*/
#endif
#ifndef USE_SERIAL5
#define USE_SERIAL5 0/*0 unused serial5 save space*/
#endif

#ifndef USE_SERIAL6
#define USE_SERIAL6 0 /*0 unused serial6 save space*/
#endif

#ifndef USE_USBSERIAL
#define USE_USBSERIAL 0 /*0 if use serial1,unused serialusb save space*/
#endif

/*USE_SPIx default 1*/
#ifndef USE_SPI1
#define USE_SPI1 0 /*0 unused spi2 save space*/
#endif

#ifndef USE_SPI2
#define USE_SPI2 0 /*0 unused spi2 save space*/
#endif

#ifndef USE_SPI3
#define USE_SPI3 0 /*0 unused spi2 save space*/
#endif

#ifndef USE_SPI4
#define USE_SPI4 0 /*0 unused spi2 save space*/
#endif

#ifndef USE_SPI5
#define USE_SPI5 0 /*0 unused spi2 save space*/
#endif

#ifndef USE_SPI6
#define USE_SPI6 0 /*0 unused spi2 save space*/
#endif

/*USE_I2Cx default 1*/
#ifndef USE_I2C1
#define USE_I2C1 0
#endif

#ifndef USE_I2C2
#define USE_I2C2 0
#endif

#ifndef USE_I2C3
#define USE_I2C3 0
#endif

#ifndef USE_I2C4
#define USE_I2C4 0
#endif

#endif
