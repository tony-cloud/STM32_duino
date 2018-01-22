/*
   Demo of ArduinoInStream and ArduinoOutStream
   This is a part of SdFat lib.  Please don't used it and SdFat at the same time
   !ArduinoStream 是SdFat库中的一部份，请不要和SdFat同时使用，使用SdFat中的输入输出流，请参照该库的demo!
*/
#include "ArduinoIOstream.h"

// create serial output stream
ArduinoOutStream cout(Serial);
// create serial input stream
ArduinoInStream cin(Serial);

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  // Wait for USB Serial
  while (!Serial) {
    yield();
  }
  delay(2000); //wait for usart link and ready
}
//------------------------------------------------------------------------------
void loop() {
  int32_t n = 0;

  cout << "\nenter an integer\n";
  cin.readline();

  if (cin >> n) {
    cout << "The number is: " << n;
  } else {
    // will fail if no digits or not in range [-2147483648, 2147483647]
    cout << "Invalid input: " << cin.buf;
  }
  cout << endl;
}
