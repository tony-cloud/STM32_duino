# STM32GENERIC
Generic implementation of Arduino for STM32 boards using STM32 HAL. This is an alternative to the [Official implementation](https://github.com/stm32duino/Arduino_Core_STM32) 

Documentation: https://danieleff.github.io/STM32GENERIC/

## Installation - Users

TODO create boards manager package

## Installation - Developers
1. Download the latest version from [https://github.com/huaweiwx/STM32GENERIC](https://github.com/huaweiwx/STM32GENERIC)
   从 [https://github.com/huaweiwx/STM32GENERIC]下载最新版本.
2. Unzip it into [Arduino]/hardware folder (Arduino must be ver1.8.5 or newer)
   将其解压到 [Arduino]/hardware 文件夹 (Arduino 必须是 ver1.8.5 或更新的)
3. Move the files in hardware/STM32GENERIC/tools folder to hardware/tools folder for allow other arduino arm can sharing it.
   将 hardware/STM32GENERIC/tools 文件夹中的文件移动到 "hardware/tools " 文件夹, 以便其他 arduino arm 可以共享它。
4. Install Arduino Zero or Arduino Sam from the board manager for the arm-none-eabi-gcc compiler.
   从板管理菜单安装 Arduino Zero 或 Arduino Sam，目的是自动安装个配置 arm-none-eabi-gcc 编译器工具链；
5. Download the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
   Recommended use GCC ver 5.4.1-2016q2,Change compiler.path in [platform.txt](https://github.com/danieleff/STM32GENERIC/blob/master/STM32/platform.txt#L21) to point to that you downloaded.
   Example for default position:  C:\Users\Administrator\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\
下载 [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)。
   建议使用 GCC 5.4-2016q3, 并解压在系统默认的工具链位置：
   C:\Users\Administrator\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc \
   也可在你下载放置的位置，但需要更改 platform.txt中的路径，让系统能找到它；
   (附注这一般是必须的，因为4 安装的是GCC4，但需要GCC 5 才支持 stm32f7，另外也使用到了GCC 5的新特性);
6. Create a folder c:\Tmp
   创建文件夹 c:\Tmp
7. Modify environment variables TEMP and TMP as: 
   修改环境变量 TEMP 和 TMP为:
   TEMP=c:\Tmp
   TMP=c:\Tmp
   Because of the Windows command line length limit, we need to modify the environment variables to compile more files (Such as uCGUI)
   这是因为 Windows 命令行有长度限制, 我们需要修改环境变量以编译更多的文件 (如 uCGUI)
