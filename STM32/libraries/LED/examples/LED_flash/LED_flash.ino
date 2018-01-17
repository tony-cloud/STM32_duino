/*
 Led_flash.ino
   This example shows how to flash an LED

 This example code is in the public domain.
 */

#include <LED.h>

void setup() {
  Led.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Led.flash(10,240,4); /*LED: on 10us, off 240us, repeat 4 times */
}
