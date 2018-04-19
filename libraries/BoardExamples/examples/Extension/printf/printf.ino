/*
 * STM32GENERIC arduino extension sample
 * printf.ino c printf demo
 * printf unsupport %f format
 * 不支持浮点和双精度数输出；
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(2000);  //wait for Serial ready.
  int32_t imax = 0x7fffffff;
  //print out
  printf("this is int32 max(dec)  : %d\n",imax);              //0x7fffffff = 2147483647
  printf("this is int32 max(hex)  : %x\n",imax);              //0x7fffffff = 2147483647
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}