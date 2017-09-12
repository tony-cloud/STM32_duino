# STM32GENERIC
Generic implementation of Arduino for STM32 boards using STM32 HAL. This is an alternative to the [Official implementation](https://github.com/stm32duino/Arduino_Core_STM32) 

Documentation: https://danieleff.github.io/STM32GENERIC/

## Installation - Users

TODO create boards manager package

## Installation - Developers

1. Download the latest version from [https://github.com/huaweiwx/STM32GENERIC](https://github.com/huaweiwx/STM32GENERIC)
2. Unzip it into [Arduino]/hardware folder
3. Move the files in hardware/STM32GENERIC/tools folder to hardware/tools folder for allow other arduino arm can sharing it.
4. Install Arduino Zero or Arduino Sam from the board manager for the arm-none-eabi-gcc compiler
5. Download the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
   Recommended use GCC ver 5.4.0-2016q2,Change compiler.path in [platform.txt](https://github.com/danieleff/STM32GENERIC/blob/master/STM32/platform.txt#L21) to point to that you downloaded.
   Example for default position:  C:\Users\Administrator\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\
6. Create a folder c:\Tmp
7. Modify environment variables TEMP and TMP as: 
   TEMP=c:\Tmp
   TMP=c:\Tmp
   Because of the Windows command line length limit, we need to modify the environment variables to compile more files (Such as uCGUI)
