/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stm32_def.h"

/*C including option*/
#include "bit_constants.h"

#ifdef __cplusplus
extern "C"{
#endif

#define HIGH 0x1
#define LOW  0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {  /*compatible with arduino sam huaweiwx@sina.com 2018.1.12*/
	LSBFIRST = 0,
	MSBFIRST = 1
};

#define CHANGE 1
#define FALLING 2
#define RISING 3


#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long long)((x)+0.5):(long long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
# define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

void init(void);
void initVariant(void);

int atexit(void (*func)()) __weak;

void pinMode(uint8_t, uint8_t);
//void digitalWrite(uint8_t, uint8_t);
//int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogReadResolution(int resolution);

#define analogReference(x)  /*huaweiwx@sina.com 2018.9*/
//void analogReference(uint8_t mode);

void analogWrite(uint8_t, int);
void analogWriteResolution(int bits);
uint8_t getAnalogWriteResolution(void);

void setPwmFrequency(uint32_t freqHz);/*add huaweiwx@sina.com 2018.8.2*/
uint32_t getPwmFrequency(void); /*add huaweiwx@sina.com 2018.8.2*/
void pwmWrite(uint8_t pin, int dutyCycle16Bits, int frequency, int durationMillis);

//unsigned long millis(void);
//unsigned long micros(void);
//void delay(unsigned long);
//void delayMicroseconds(uint32_t us);

uint32_t shiftIn( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder ); //add by huaweiwx@sina.com
void shiftOut( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder, uint8_t ucVal ); //add by huaweiwx@sina.com

//void attachInterrupt(uint8_t, void (*)(void), int mode);
//void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

#define analogInPinToBit(P) (P)
#define digitalPinToPort(P) ( variant_pin_list[P].port )
#define digitalPinToBitMask(P) ( variant_pin_list[P].pinMask )
#define portOutputRegister(P) ( &(P->ODR) )
#define portInputRegister(P) ( &(P->IDR) )
#define IS_ARDUINO_PIN(PIN)  ((PIN) < NUM_DIGITAL_PINS)
// #define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
// #define analogInPinToBit(P) (P)
// #define portInputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_input_PGM + (P))) )
// #define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (P))) )

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_AN_INTERRUPT -1

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "WCharacter.h"

#if defined(HAVE_HWSERIAL0) && defined(HAVE_CDCSERIAL)
# error "Targets with both UART0 and CDC serial not supported"
#endif

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

//unsigned long pulseIn(uint32_t pin, uint32_t state, unsigned long timeout = 1000000L);
//unsigned long pulseInLong(uint32_t pin, uint32_t state, unsigned long timeout = 1000000L);

extern "C" void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
extern "C" void noTone(uint8_t pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif

#include "stm32_clock.h"
#include "stm32_gpio.h"
#include "wiring_pulse.h"  /*copy from Arduino_core_STM32 huaweiwx@sina.com 2017.11*/
#include "stm32_debug.h"


#ifdef __cplusplus

#include "HardwareSerial.h"
#include <SerialUSB.h>
#include <STM32System.h>

/*C++ including option*/
#if USE_ARDUINOSTREAMING
#  include <Streaming.h>
#endif

#ifndef Serial /*cal overload by HAL_Config.h*/
# if defined(MENU_SERIAL)
#   define Serial MENU_SERIAL
# elif defined(MENU_SERIAL_AUTO)
#   define Serial MENU_SERIAL_AUTO
# endif
#endif

#endif


#endif
