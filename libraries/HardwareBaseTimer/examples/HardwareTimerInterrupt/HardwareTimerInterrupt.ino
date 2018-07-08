/*
 * STM32 基本定时器 TIM6/7 库lib
 * STM32 basic timers TIM6/7 lib: HardwareBaseTimer by huaweiwx<huaweiwx@sina.com>
 *
 * This example sets basic timers(TIM6 and TIM7) software interrupt
 *
 * note: if  used freeRTOS, Timer7 is undefined 
 * 注：即使芯片有TIM7 , 如果运行了 freeRTOS ，该库 Timer7 就不会定义，因为freeRTOS优先使用TIM7作为系统时钟；
 *
 * Advanced-control timers and General-purpose timers you can use the HardwareTimer lib.
 * 要使用到其他普通定时器和高级定时器TIM1~5/8~17/21~22(视所选板载芯片)的定时、PWM或脉冲捕捉等高级用途 ，可用HardwareTimer lib。 
 * 
 * 2018.5.28 huaweiwx<huaweiwx@sina.com>
*/

#include "HardwareBaseTimer.h"

#define Timerx Timer6

void interrupt() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    Timerx.setPeriod(1000000); // in microseconds = 1 second

    Timerx.attachInterrupt(interrupt);
    Timerx.resume();
}

void loop() {
    delay(5000);

    Serial.println("----");

    Serial.print("PCLK1Freq: ");
    Serial.println(HAL_RCC_GetPCLK1Freq());
    
    Serial.print("Timer base frequency:");
    Serial.println(Timerx.getBaseFrequency());

    Serial.print("Timer prescaler:");
    Serial.println(Timerx.getPrescaleFactor());

    Serial.print("Timer period:");
    Serial.println(Timerx.getOverflow());
}
