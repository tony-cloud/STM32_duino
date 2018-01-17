/*
 *  doubleNum.ino double to strnig and double stream out demo， max 15-digit Active number.
 *  arm增强 转换64bit双精度数为字符串及双精度数流输出 演示和样板，最大15位有效数；
 */

#include "streaming.h"

  // the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  double pi = PI*100000000;
  Serial.begin(115200);
  delay(2000);

  //print out
  Serial.println(pi);                 //out:3.14159265358979  15-digit Active number
  Serial.println(round(pi));

  //double to str
  Serial << String(pi,14) << endl;    //out:3.14159265358979  15-digit Active number

  //double steam out
  Serial << _DOUBLE(pi,14) << endl;   //out:3.14159265358979 15-digit Active number

  //compare float
  Serial << _FLOAT(pi,14) << endl;    //out:3.14159274101257  8-digit Active number
}

 //the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

