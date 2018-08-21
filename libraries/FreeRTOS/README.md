
## FreeRTOSConfig.h 配置文件

### 1. FreeRTOS Search Profile FreeRTOSConfig.h and use the following order of precedence. 搜索 FreeRTOSConfig.h,并按下述优先顺序使用

-  Current project directory  当前工程所在目录
-  Current Board Definition directory 当前板子定义目录: [variant]/configs/
-  FreeRTOS/default/

---

### 2. Some definitions can be changed by HAL_Conf.h in current project directory
###   许多常用的内部定义可以通过当前工程所在目录的文件 HAL_Conf.h 改变

---

### 3. FreeRTOS port. 系统定制

-  	`portUSE_HEAP` Memory management 1~5  use 'HEAP_x.c' default 4
-  	`portTickUSE_TIMx` use  systic or TIMx  to schedule

--- 

### 4. The following API features are disable by default, and need to be set to 1 in the Hal_conf.h file when using these features:
###    下述API功能缺省是关闭的,当使用这些功能时需要在HAL_Conf.h文件中设置为1:

- configUSE_COUNTING_SEMAPHORES
- INCLUDE_vTaskDelayUntil
- configUSE_IDLE_HOOK
- configUSE_TICK_HOOK

---

## Known Issues (已知问题)
1. `GCC 5.4.2-2016q2`: `srand(x)` and `rand()` have a bug for STM32H7,running into HardFault_Handler (`FreeRTOSBookExamples\Example015` and `FreeRTOSBookExamples\Example016`);
2. `GCC 7.3.1-2018q2`: There are build err to STM32H7
3. IF unused STM32H7 board then recommended using `GCC 5.4.2-2016q2` else using `GCC 6.3.1-2017q2` but unsupported to `ArduinoSTL lib`         