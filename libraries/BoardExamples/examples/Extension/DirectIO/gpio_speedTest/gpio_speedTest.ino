/*
  gpio_speedTest.ino arduino gpio speed test example for stm32/efm32
  
  mode 5:  use avr emulate class;
  mode 4:  use bitband macro define;
  mode 3:  use LL_PIN class
  mode 2:  use BB_PIN class (for M3/M4 only others LL_BIN)
  mode 1:  cplus mode
  mode 0:  c mode
  
  NUCLEO_F401 84M  run in sram:
	read:	  8403khz 119us  mode 1/3/5
		      6493khz 154us  mode 4
		      7633khz 131us  mode 2
		      2793khz 358us  mode 0

	write:	  7936khz 126us  mode 1/3/5
		      5076khz 197us  mode 4
		      3663khz 273us  mode 2
	      	1757khz 569us  mode 0
         
  by  huawei <huaweiwx@sina.com>   2019.9.10
*/

/* select mode 0/1/2/3/4/5 */
#define GPIOMODE 5


#if  GPIOMODE == 5  /*avr emulate*/
/*for NUECLEO_64 the LED_BUILTIN is PA5 */
	#define OUT_DDR  DDRA
	#define OUT_PORT PORTA
	#define OUT_MASK bit(5)
	#define IN_PIN   bitRead(PINA,0)
#elif GPIOMODE == 4  /*bitband macro M3/M4 only*/
    #define OUT_PIN PAout(5)
    #define IN_PIN PAin(0)
#elif GPIOMODE == 3 /*LL_Pin class */
    GPIOPIN OUT_PIN(LED_BUILTIN);
    GPIOPIN IN_PIN(PA0);
#elif GPIOMODE == 2  /*BB_PIN class */
    BB_PIN OUT_PIN(LED_BUILTIN);
    BB_PIN IN_PIN(PA0);
#elif GPIOMODE == 1        /* cplus mode */
    ARDUINOPIN_TypeDef OUT_PIN = LED_BUILTIN;   /* led is __ConstPin class type */
    ARDUINOPIN_TypeDef IN_PIN = PA0;
#else                      /* c mode */
    uint8_t OUT_PIN = LED_BUILTIN;
    uint8_t IN_PIN = PA0;
#endif

void setup() {
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  delay(2000);
#if GPIOMODE == 5
  OUT_DDR |= bit(5);
#elif GPIOMODE == 4
  pinMode(LED_BUILTIN, OUTPUT);
#elif GPIOMODE >= 2
  OUT_PIN.mode(OUTPUT);
#else
  pinMode(OUT_PIN, OUTPUT);
#endif

  uint32_t timers = getTimers(1000, 0);
  Serial.println("\nRead:");
  Serial.print(1000000 / timers);
  Serial.print(" khz  Timer elapsed:");
  Serial.print(timers);
  Serial.println(" us\n");

  timers = getTimers(1000, 1);
  Serial.println("Write:");
  Serial.print(1000000 / timers);
  Serial.print(" khz  Timer elapsed:");
  Serial.print(timers);
  Serial.println(" us\n");
}

//Measuring toggle frequency with an oscilloscope:
void loop() {
#if  GPIOMODE == 5
  OUT_PORT ^= OUT_MASK;
#elif  GPIOMODE == 4
  digitalToggle(OUT_PIN);
#elif   GPIOMODE >= 2
  OUT_PIN.toggle();
#else
  digitalToggle(OUT_PIN);
#endif
  //  delay(500);
}


uint32_t getTimers(uint32_t count, uint8_t op) {
  uint32_t timeBegan, loopTimeElapsed, timeElapsed, i;
  i = 0;
  uint32_t tmp = 0;
  timeBegan = micros();
  while (i < count) {
    i++;
  }
  loopTimeElapsed = (micros() - timeBegan); // Time taken to do nothing but increment a variable
  i = 0;
  if (op) {  //write
    timeBegan = micros();
    while (i < count) {
#if   GPIOMODE == 5
	  OUT_MASK |=  OUT_MASK;
      OUT_MASK &= ~OUT_MASK;
#elif   GPIOMODE == 4
      OUT_PIN = 1;
      OUT_PIN = 0;
#elif   GPIOMODE >= 2
      OUT_PIN.write(HIGH);
      OUT_PIN.write(LOW);
#else
      digitalWrite(OUT_PIN, HIGH);
      digitalWrite(OUT_PIN, LOW);
#endif
      i++;
    }
    timeElapsed = (micros() - timeBegan - loopTimeElapsed); // Time taken to write a pin
  } else { //read
    timeBegan = micros();
    while (i < count) {
#if    GPIOMODE == 5
      tmp += IN_PIN;
#elif  GPIOMODE == 4
      tmp += IN_PIN;
#elif  GPIOMODE >= 2
      tmp += IN_PIN.read();
#else
      tmp += digitalRead(IN_PIN);
#endif
      i++;
    }
    timeElapsed = (micros() - timeBegan - loopTimeElapsed); // Time taken to read a pin
  }
  return timeElapsed;
}

