/*
  LED.h - LED library head file
  huaweiwx@sina.com 2017.  All right reserved.

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
#ifndef __LIB_LED_h__
#define __LIB_LED_h__

#include <Arduino.h>

#ifdef LED7_BUILTIN
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN,LED3_BUILTIN,LED4_BUILTIN,LED5_BUILTIN,LED6_BUILTIN,LED7_BUILTIN
#elif defined(LED6_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN,LED3_BUILTIN,LED4_BUILTIN,LED5_BUILTIN,LED6_BUILTIN
#elif defined(LED5_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN,LED3_BUILTIN,LED4_BUILTIN,LED5_BUILTIN
#elif defined(LED4_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN,LED3_BUILTIN,LED4_BUILTIN
#elif defined(LED3_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN,LED3_BUILTIN
#elif defined(LED2_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN,LED2_BUILTIN
#elif defined(LED1_BUILTIN)
#define LEDS_LIST LED_BUILTIN,LED1_BUILTIN
#elif defined(LED_BUILTIN)
#define LEDS_LIST LED_BUILTIN
#else
#warning  "unstandard arduino board "	
#define LEDS_LIST 13	
#endif

#define LED_FADEAMOUNT 5

typedef struct {
    uint8_t  pin;
    uint8_t  on;
    uint8_t  off;
    uint8_t  status;
	int brightness;    // how bright the LED is
    int fadeAmount;    // how many points to fade the LED by
	int fadeTime; /* = (1000/(255/LED_FADEAMOUNT));*/
} LED_TypeDef;

#ifdef __cplusplus
extern "C"{
#endif

void LEDFlash(uint8_t pin,uint16_t timeon,uint16_t timeoff,uint8_t cnt,uint8_t on);  //add by huawei 2015.3

#ifdef __cplusplus
} //extern "C"{

class LEDClass 
{
 public:
	LEDClass(uint8_t pin=LED_BUILTIN, uint8_t on=LOW);
	
	inline void Init(void) __attribute__((always_inline)){
			pinMode(pdata->pin,OUTPUT);
	}
	
    void setPin(uint8_t pin, uint8_t on=LOW);

	inline void on(void) __attribute__((always_inline)){    //digitalWrite
		digitalWrite(pdata->pin,pdata->on);
		pdata->status =pdata->on;
	}
    inline void on(int val) __attribute__((always_inline)){ //analogWrite
		analogWrite(pdata->pin, (pdata->on? val:255-val));
	}
#ifdef STM32GENERIC
//analogWrite
	bool availablePwm(void){return true;};	
#elif defined(__MSP430__)
    bool availablePwm(void){return  availablepwm;} ;
    bool availablepwm;
#else
    bool availablePwm(void){return  availablepwm;} ;
    bool availablepwm = true;   /*fixed me*/
#endif

    inline LEDClass &operator = (bool value) __attribute__((always_inline)){
		digitalWrite(pdata->pin,value);
		return *this;
    }

	inline void off(void) __attribute__((always_inline)){
		digitalWrite(pdata->pin,pdata->off);
		pdata->status = pdata->off;
	}

	inline void toggle(void) __attribute__((always_inline)){
		if(pdata->status == pdata->off) this->on();
		else this->off();
	}

	inline void flash(uint16_t timeon,uint16_t timeoff,uint8_t cnt=1) __attribute__((always_inline)){
		LEDFlash(pdata->pin, timeon,timeoff,cnt,pdata->on);
		pdata->status = pdata->off;
	}

	void fade(uint16_t time = (1000/(255/LED_FADEAMOUNT)));

    LED_TypeDef* pdata;

  private:
    LED_TypeDef  sLed;
};

#ifdef LED_BUILTIN
extern LEDClass Led;
extern LEDClass LEDs[];
#endif

#ifdef LED1_BUILTIN
extern LEDClass Led1;
#endif

#ifdef LED2_BUILTIN
extern LEDClass Led2;
#endif

#ifdef LED3_BUILTIN
extern LEDClass Led3;
#endif

#ifdef LED4_BUILTIN
extern LEDClass Led4;
#endif

#ifdef LED5_BUILTIN
extern LEDClass Led5;
#endif

#ifdef LED6_BUILTIN
extern LEDClass Led6;
#endif

#ifdef LED7_BUILTIN
extern LEDClass Led7;
#endif

#endif /*__cplusplus*/

#endif /*__LIB_LED_h__*/

