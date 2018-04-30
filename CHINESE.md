# STM32GENERIC简介
STM32GENERIC是STM32在Arduino平台上的通用接口(STM32 HAL).这是一个[ST官方项目](https://github.com/stm32duino/Arduino_Core_STM32)的替代方案 
STM32GENERIC与其他类型的stm32duino相比的优势:
1.支持更多的开发板。
2.兼容性更好，例如Adafruit库不需要任何修改即可直接在STM32GERENIC编译使用。
3.有中文文档支持(建设中)。

英文文档: https://danieleff.github.io/STM32GENERIC/
中文文档: Work in progress, 你可以在[这里](https://github.com/tony-cloud/STM32GENERIC-DOC)提交issue和pull request来向我们提供帮助

**提示:STM32GENERIC虽然努力让函数更接近avr Arduino,但是不支持avr单片机的寄存器操作，带有寄存器操作的代码会导致编译失败！**

## 安装

~~未实现 添加开发板管理器的支持~~
开发板管理器文件已经完成并且测试成功
你只需要添加下面的地址到附加开发板管理器网址（Arduino IDE > 文件 > 首选项 >附加开发板管理器网址 > 好） 

https://raw.githubusercontent.com/tony-cloud/STM32BoardManagerFiles/master/STM32/package_tony_stm32_index.json

在 工具 > 开发板 > 开发板管理器 等待下方读条完毕，然后划到底部，找到STM32GENERIC,在左下角下拉菜单选择版本号最高的一项，点击安装

等待安装完毕，下方没有橙字报错说明安装成功了，然后你可以在 工具 > 开发板 菜单向下滑动滚轮即可看到新添加的开发板

## 使用

选择开发板之后，在工具菜单选择具体芯片或者版型(Specific Board)，选择下载方式(upload method)和端口, 最后 项目 > 上传 ,程序会自动编译并且上传

如果你不会使用Arduino,你可以尝试在[Arduino中文社区](https://www.arduino.cn/thread-1066-1-1.html)查看教程
