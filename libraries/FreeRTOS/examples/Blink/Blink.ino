/*
  Blink.ino
  Turns on 2 LEDs on/off use LEDClass, demo running in FreeRTOS V9.0.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.
  modified for STM32GENERIC   by huaweiwx@sina.com , May 2 2017
*/

#include <FreeRTOS.h>
#include <Streaming.h>
#include <LED.h>   /*LEDClass: Led Led1/2/3/4/5/6/7 has be predefiend */

static void myTask1(void  __attribute__ ((unused)) *argument)
{
  /*Task1 setup*/
  uint32_t i = 0;
  Led.Init();
  Serial.begin(115200);

  /* Infinite loop */
  for (;;)
  {
  /* USER CODE BEGIN Task1 */
    Led.flash(50,950,1);
    i++;
    Serial << "Count:" << _HEX(i) << " in myTask1\n";
  /* USER CODE END Task1 */
   }
}

#if defined(LED1_BUILTIN)
static void myTask2(void __attribute__ ((unused)) *argument)
{
  /*Task2 setup*/
  Led1.Init();
  
  /* Infinite loop */
  for (;;)
  {
  /* USER CODE BEGIN Task2 */
    Led1.flash(50,200,1);
  /* USER CODE END Task2 */
  }
}
#endif

// the setup function runs once when you press reset or power the board.
void setup() {
  xTaskCreate(myTask1,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY + 1,
              NULL);
#if defined(LED1_BUILTIN)
  xTaskCreate(myTask2,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY + 2,
              NULL);
#endif
  vTaskStartScheduler();  //FreeRTOS start and never return!
  _Error_Handler(__FILENAME__, __LINE__);
}

/****************  default idle hook callback if configUSE_IDLE_HOOK ***************************
 * 1  STM32GENERIC loop() is call by default idle hook if enable(set configUSE_IDLE_HOOK to 1) *
 * 2  Idle loop has a very small stack (check or set configMINIMAL_STACK_SIZE)                 * 
 * 3  Loop must never block.                                                                   * 
 * 4  This default idle hook can be overload by vApplicationIdleHook()                         * 
 ***********************************************************************************************/
void loop() {
  for(;;){} //This example Not used.
}
