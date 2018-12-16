/*
  avr_emulation.ino: avr registers PORTx PINx DDRx emulation demo

  EFM32/STM32  avr emulation is build in; huaweiwx@sina.com 2018.8.10
*/

#ifdef ARDUINO_NUCLEO_F401RE   /**/
/*for NUECLEO_64 the LED_BUILTIN is PA5 */
  #define LED_DDR  DDRA
  #define LED_PORT PORTA
  #define pinMask  bit(5)
#else
/*for NUECLEO_144 the LED_BUILTIN is PB0 */
  #define LED_DDR  DDRB     /*fixed me*/
  #define LED_PORT PORTB    /*fixed me*/
  #define pinMask  bit(0)    /*fixed me*/
#endif

void setup() {
  LED_DDR |= pinMask;   //set LEDPIN  OUTPUT
}
// the loop function runs over and over again forever
void loop() {
#if 1 
  LED_PORT ^=  pinMask;   //LEDPIN toggle
  delay(1000);
#else
  LED_PORT |=  pinMask;   //LEDPIN high
  delay(1000);
  LED_PORT &= ~pinMask;   //LEDPIN low
  delay(1000);
#endif
}
