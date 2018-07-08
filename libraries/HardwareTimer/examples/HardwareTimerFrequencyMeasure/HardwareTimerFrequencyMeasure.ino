/*
* This example measures input frequency
*
* Select your board in https://danieleff.github.io/STM32GENERIC/ "STM32 Board" menu
*
* Check timer for which pin is the default TIM1/CH1 connected
*
* Check your board pinout which pin it is.
*
* Connect the testPwmPin to the previous input capture pin
*
* On Serial, you should see default PWM frequency
*/

#include "HardwareTimer.h"

#define Timerx Timer1
const int testPwmOutputPin = PA1;
const int testChannel = 1;  //(TIM1 channel1 is PA8) channel: 1 ~ 6  

void setup() {
    analogWrite(testPwmOutputPin, 128);

    Serial.begin(115200);

    Timerx.setPrescaleFactor(100);
    Timerx.setOverflow(UINT16_MAX);

    Timerx.setMode(testChannel, TIMER_INPUT_CAPTURE_RISING); 
    Timerx.resume();
}

void loop() {
    uint32_t start = Timerx.getCompare(testChannel);
    uint32_t end;
    do {
        //Wait for next rising edge
        end = Timerx.getCompare(testChannel);
    } while(end == start);

    uint32_t diff;
    if (end > start) {
        diff = end - start;
    } else {
        diff = (Timerx.getOverflow() - start) + end;
    }
    uint32_t timerFrequency = Timerx.getBaseFrequency() / (Timerx.getPrescaleFactor() + 1);

    Serial.print("Input frequency: ");
    Serial.print((float)timerFrequency / diff, 6);
    Serial.println(" Hz");

    delay(1000);
}
