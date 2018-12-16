/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */
#include "exteeprom.h"

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {
  // initialize serial and wait for port to open:
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  delay(1000);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

/* for stl c++11/14 the begin/end is keywords for iteration. 
   while set USE_ITERATOR to 1 should be use  Init/deInit instead with them.
 */
#if USE_ITERATOR >0
  EEPROM.Init(); /* Init ExtEEPROM gpio */
#else
  EEPROM.begin(); /* Init ExtEEPROM gpio */
#endif

}

void loop() {
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.
    
    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/
  digitalToggle(LED_BUILTIN);
  delay(500);
}
