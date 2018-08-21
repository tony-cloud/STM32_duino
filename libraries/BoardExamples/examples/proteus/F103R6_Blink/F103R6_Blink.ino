/*
  Blink.ino for proteus8.x
  Turns an LED on for  0.5 second, then off for 0.5 second, repeatedly.

  build for proteus8.x:
     1 copy this sketch folder F103R6_Blink to Documents/Arduino
	 2 open it from Arduino IDE
     3 selected F103R/C/T_4/6 from menu toos->board
	 4 selected F103R6[LED PC13]
	 5 selected 8M(HSI)_8M(for proteus) because proteus unsupport stm32 PLL setup
     6 selected SerialUART1 or SerialUART2
     7 selected Export compiled Binay from menu Sketch
	 8 run Documents/Arduino/F103R6_Blink/F103R6_Blink.pdsprj from proteus 8.7 sp3

  huaweiwx@sina.com  2018.8.2
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(1000);
  Serial.println("hello world! your key input:");
  Serial2.println("your input is:");
}

// the loop function runs over and over again forever
void loop() {
  digitalToggle(LED_BUILTIN);   // turn the LED_BUILTIN on/off
  while (Serial.available()) {
    int ch = Serial.read();
    Serial2.write((uint8_t)ch);
  }
  delay(500);                  // wait for 0.5 second
}

