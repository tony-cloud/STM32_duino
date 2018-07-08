/*
* This example sets timer1 / channel1 to 10% PWM
*
* Select your board in https://danieleff.github.io/STM32GENERIC/ "STM32 Board" menu
*
* Check timer for which pin is the default TIM1/CH1 connected
*
* Check your board pinout which pin it is.
*
* Use scope / logic analyzer to check PWM output
*/

#include "HardwareTimer.h"
#define Timerx Timer2
int testPwmOutputPin = PA5;
int testChannel = 1;

void setup() {
    Timerx.setPrescaleFactor(65535);
    Timerx.setOverflow(99); //Period

    Timerx.setCompare(testChannel, 10);  //testChannel / Duty cycle
    Timerx.setMode(testChannel, TIMER_PWM,testPwmOutputPin);

    //Timer1.setMode(testChannel, TIMER_PWM, testPwmOutputPin);      // Alternatively for non-default pin. Check chip documentation!
    //Timer1.setMode(testChannel, TIMER_OUTPUT_COMPARE_TOGGLE);      // Pin toggles when counter reaches compare (effectively 50% PWM)

    Timerx.resume(testChannel,TIMER_PWM);
}

void loop() {

}
