# STM32LowPower Lib
Arduino library to support STM32 Low Power(低功耗库).

## API

* **`void begin()`**: configure the Low Power

* **`void idle(uint32_t millis)`**: enter in idle mode
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void sleep(uint32_t millis)`**: enter in sleep mode  
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void deepSleep(uint32_t millis)`**: enter in deepSleep mode  
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void shutdown(uint32_t millis)`**: enter in shutdown mode
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the board in millis milliseconds.

* **`void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode)`**: Enable GPIO pin in interrupt mode. If the pin is a wakeup pin, it is configured as wakeup source (see board documentation).  
**param** pin: pin number  
**param** callback: pointer to callback  
**param** mode: interrupt mode (HIGH, LOW, RISING, FALLING or CHANGE)  

* **`void enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback)`**: enable a UART peripheral in low power mode. See board documentation for low power mode compatibility.  
**param** serial: pointer to a UART  
**param** callback: pointer to a callback to call when the board is waked up.  

* **`void enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void * data)`**: attach a callback to the RTC peripheral.  
**param** rtc: pointer to RTC. Could be NULL as RTC is a Singleton.  
**param** callback: pointer to a callback to call when the board is waked up.  
**param** callback: data: optional pointer to callback data parameters (default NULL).  

* **`void enableWakeupFrom(TwoWire *wire, voidFuncPtrVoid callback)`**: enable an I2C peripheral in low power mode. See board documentation for low power mode compatibility. **Currently not available.**  
**param** wire: pointer to I2C  
**param** callback: pointer to a callback to call when the board is waked up.  


`Begin()` function must be called at least once before `idle()`, `sleep()`, `deepSleep()` or `shutdown()` functions.  

`attachInterruptWakeup()` or `enableWakeupFrom()` functions should be called before `idle()`, `sleep()`, `deepSleep()` or `shutdown()` functions.  

HardwareSerial used as Wakeup source will configure it to use HSI clock source even if another peripheral clock is configured.

RTC used as Wakeup source will configure it to use LSE clock source even if another RTC clock source is selected.

The board will restart when exit the shutdown mode.  

## 功能函数一览:
* **`void begin()`**:  开始配置 LowPower
* **`void idle(uint32_t millis)`**:  进入空闲(idle)模式
* **`void sleep(uint32_t millis)`**:  进入睡眠(sleep)模式
* **`void deepSleep(uint32_t millis)`**:  进入深度睡眠(deep sleep)模式
* **`void shutdown(uint32_t millis)`**:  进入停机(shutdown)模式
**参数**  millis (可选): 在退出该模式前的毫秒数，最小1000 ms. 通过RTC 的 alarm 模式 唤醒板子在 millis 毫秒后。

* **`void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode)`**: 设置 GPIO pin 中断，通过该pin 中断从(idle/sleep/deepsleep)唤醒, 如果该脚配置为唤醒源(见相关文档)，如PA0)则可从shutdowm模式唤醒板子。
**参数** pin: pin number(arduino脚号)
     callback: pointer to callback(中断回调函数)
     mode: 中断模式(HIGH, LOW, RISING, FALLING or CHANGE) 

* **`void enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback)`**: 允许串口(USART/UART)低功耗模式,从(idle/sleep/deepsleep)模式唤醒(见相关文档),如有低功耗串口(LPUART),还可从关机(shutdown)模式唤醒(见相关文档).  
**参数** serial: arduino 硬件串口如 Serial 
     callback: (中断唤醒回调函数).  

* **`void enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void * data)`**: 允许RTC唤醒
**参数**  rtc: pointer to RTC.  
**参数**  callback: (中断唤醒回调函数). 
**参数**  callback: data: 可选的回调数据指针(default NULL).  

* **`void enableWakeupFrom(TwoWire *wire, voidFuncPtrVoid callback)`**: 允许I2C唤醒（未完成，暂不支持）

`Begin()`该函数必须在 `idle()`, `sleep()`, `deepSleep()` or `shutdown()`前调用一次。  
`attachInterruptWakeup()` or `enableWakeupFrom()`在 `idle()`, `sleep()`, `deepSleep()` or `shutdown()`前调用。
HardwareSerial 用于唤醒源时配置为 HSI clock source 而不论已配置的任何时钟源.
RTC用于唤醒源使用 LSE 而不论已配置的其他任何时钟源.
从shutdown 模式退出，板子将重启,因为进入该模式后，除后备电源供电的寄存器和sram外，所有内部电源都已关闭及这些电源供电的所有ram和寄存器内容均已消失。
  
## Hardware state 硬件状态

* **Idle mode**: low wake-up latency (µs range) (e.g. ARM WFI). Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself.
低唤醒延迟 (µs 范围) (如 ARM WFI)。记忆和电压供应被保留。最小节电主要集中在核心本身。

* **sleep mode**: low wake-up latency (µs range) (e.g. ARM WFI), Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself but
higher than idle mode.
低唤醒延迟 (µs 范围) (如 ARM WFI), 记忆和电压供应被保留。最小节电主要在核心本身, 但高于空闲（Idle）模式。

* **deep sleep mode**: medium latency (ms range), clocks are gated to reduced. Memories
and voltage supplies are retained. If supported, Peripherals wake-up is possible (UART, I2C ...).
中等延迟 (ms 范围), 时钟降低。记忆和电压供应被保留。如果支持, 可通过外围设备(UART, I2C...)唤醒 。

* **shutdown mode**: high wake-up latency (posible hundereds of ms or second timeframe), voltage supplies are cut except always-on domain, memory content are lost and system basically reboots.
高唤醒延迟 (ms 或上百秒时间范围内), 除后备电源供电的寄存器和sram外, 还会切断电压供应，因此由这些电源供电的所有ram和寄存器内容均已丢失, 系统基本需要重新启动。

## Source
You can find the source files at  
https://github.com/stm32duino/STM32LowPower
