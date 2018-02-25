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
#include "util/bitband.h"

#ifdef STM32GENERIC
 #if __has_include(<FreeRTOS.h>)   
  #include <FreeRTOS.h>
  #define  LED_DELAY(x) vTaskDelay(x)
 #else
  #define  LED_DELAY(x) delay(x)		 
 #endif
#else
 #define  LED_DELAY(x) delay(x)	
#endif

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


#ifdef LED_BUILTIN_MASK
# define LED_MASK LED_BUILTIN_MASK
#elif defined(STM32_LED_BUILTIN_ACTIVE_LOW)
# define LED_MASK 0
#else
# define LED_MASK 0xff
#endif

#define LED_FADEAMOUNT 5

typedef struct {
	int brightness;    // how bright the LED is
    int fadeAmount = LED_FADEAMOUNT;    // how many points to fade the LED by
	int fadeTime  = (1000/(255/LED_FADEAMOUNT));
} LED_TypeDef;

struct _FLASH
{ 
  int timeon;
  int timeoff;
  int count;
  _FLASH(int on,int off,int cnt=1): timeon(on),timeoff(off),count(cnt) 
  {}
};

template<const int pin, const bool onval=false>
class LEDClass : public BB_PIN<pin>{
 public:
    inline LEDClass &operator = (bool value) __attribute__((always_inline)){
		this->write(value);
		return *this;
    }

    inline LEDClass & operator << (bool value) __attribute__((always_inline)) {
		this->write(value);
		return *this;
    }

    inline LEDClass & operator << (int value) __attribute__((always_inline)) {
		this->write((bool)value);
		return *this;
    }

    inline LEDClass & operator << (const _FLASH &arg) __attribute__((always_inline)) {
		this->flash((uint16_t)arg.timeon,(uint16_t)arg.timeoff,(uint8_t)arg.count);
		return *this;
    }

	inline void Init(void){this->mode(OUTPUT);}

    inline void on(void) __attribute__((always_inline)){
		this->write(onval?1:0);
    }

    inline void off(void) __attribute__((always_inline)){
		this->write(onval?0:1);
    }
	
	void flash(uint16_t timeon,uint16_t timeoff,uint8_t cnt=1){
	  for(uint8_t i=cnt;i>0;i--){
		this->on();
		if(timeon)
		  LED_DELAY(timeon);
		this->off();
		if(timeoff)
		  LED_DELAY(timeoff);
	  }
	}

    inline void on(int val) __attribute__((always_inline)){ //analogWrite
	    uint8_t res = getAnalogWriteResolution();
		uint32_t max = (1<<res)-1;
		val &=max;
		analogWrite(pin, (onval? val:max-val));
	}


    void fade(uint16_t time) {
      if(time < sLed.fadeTime) time = sLed.fadeTime;	
        for(volatile uint16_t i =0; i<(time/sLed.fadeTime);i++){
           analogWrite(pin, sLed.brightness);

     // change the brightness for next time through the loop:
           sLed.brightness +=  sLed.fadeAmount;

     // reverse the direction of the fading at the ends of the fade:
        if ((sLed.brightness <= 0) || (sLed.brightness >= 250)) {
           sLed.fadeAmount = -sLed.fadeAmount;
        }
     LED_DELAY(sLed.fadeTime);
      }
  }
  
  void fade(){ 
    fade(1000/(255/LED_FADEAMOUNT));
  }
  
  LED_TypeDef* pdata;

  private:
    LED_TypeDef  sLed;
};

#ifdef LED_BUILTIN
extern LEDClass<LED_BUILTIN, bitRead(LED_MASK,0)>Led;
#endif

#ifdef LED1_BUILTIN
extern LEDClass<LED1_BUILTIN, bitRead(LED_MASK,1)>Led1;
#endif

#ifdef LED2_BUILTIN
extern LEDClass<LED2_BUILTIN, bitRead(LED_MASK,2)>Led2;
#endif

#ifdef LED3_BUILTIN
extern LEDClass<LED3_BUILTIN, bitRead(LED_MASK,3)>Led3;
#endif

#ifdef LED4_BUILTIN
extern LEDClass<LED4_BUILTIN, bitRead(LED_MASK,4)>Led4;
#endif

#ifdef LED5_BUILTIN
extern LEDClass<LED5_BUILTIN, bitRead(LED_MASK,5)>Led5;
#endif

#ifdef LED6_BUILTIN
extern LEDClass<LED6_BUILTIN, bitRead(LED_MASK,6)>Led6;
#endif

#ifdef LED7_BUILTIN
extern LEDClass<LED7_BUILTIN, bitRead(LED_MASK,7)>Led7;
#endif

#endif /*__LIB_LED_h__*/

