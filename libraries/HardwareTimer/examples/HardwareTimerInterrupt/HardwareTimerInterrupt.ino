/*
* This example sets timerx software interrupt
* add TIM5/8~17 for all chip if have by huaweiwx@sina.com  
*/

#include "HardwareTimer.h"
//#define Timerx Timer1
#define Timerx Timer13

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
