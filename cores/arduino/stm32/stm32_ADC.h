/*
  Copyright (c) 2018 huaweiwx<huaweiwx@sina.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef __STM32ADC_H__
#define __STM32ADC_H__

#pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  include "stm32_HAL/stm32XXxx_ll_adc.h"
#pragma GCC diagnostic pop

#ifdef STM32H7
# define INTERNAL_Instance ADC3
# define ADC_CHANNEL_VBAT ADC_CHANNEL_VBAT_DIV4
#else
# define INTERNAL_Instance ADC1
#endif

#ifdef ADC_RESOLUTION_16B
# define MAX_RESOLUTION  16
#else
# define MAX_RESOLUTION  12
#endif

#define MAX_CONVERTED_VALUE   (1U<<MAX_RESOLUTION)     /* Max converted value 16B/12B */

#define AMBIENT_TEMP              25.0     /* Ambient Temperature */
#if defined(STM32F1)
#define INTERNAL_TEMPSENSOR_AVGSLOPE   ((int32_t) 4300)        /* Internal temperature sensor, parameter Avg_Slope (unit: uV/DegCelsius). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25        ((int32_t) 1430)        /* Internal temperature sensor, parameter V25 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25_TEMP   25.0
#define INTERNAL_TEMPSENSOR_V25_VREF   ((int32_t) 3300)
//#define VSENS_AT_AMBIENT_TEMP     1430     /* VSENSE value 1.43(v) at ambient temperature */
//#define AVG_SLOPE                 43.0     /* 4.3 mV Avg_Solpe multiply by 10 */
#elif defined(STM32F2)||defined(STM32F4)
#define INTERNAL_TEMPSENSOR_AVGSLOPE    2500.0        /* Internal temperature sensor, parameter Avg_Slope (unit: uV/DegCelsius). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25         760.0        /* Internal temperature sensor, parameter V25 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25_TEMP    25.0
#define INTERNAL_TEMPSENSOR_V25_VREF    3300.0
#else
#define VSENS_AT_AMBIENT_TEMP     760     /* VSENSE value 0.76(v) at ambient temperature */
#define AVG_SLOPE                 25.0     /* Avg_Solpe multiply by 10 */
#endif

#ifndef VDDA_APPLI
#define VDDA_APPLI                     3300
#endif

#ifndef ADC_VBAT_MULTI
#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
#define ADC_VBAT_MULTI			2
#else
#define ADC_VBAT_MULTI			4
#endif
#endif

#ifndef VREFINT
#define VREFINT 1200
#endif

#ifdef __cplusplus
extern "C"  {
#endif

void analogReadResolution(int resolution);

int analogReadResolutionVal(void);

#ifdef   ADC_SINGLE_ENDED
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode);
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode,uint8_t n);
#else
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch);
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch,uint8_t);
#endif

#ifdef __cplusplus
} //extern "C"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
class ADCClass {
  public:
    inline void resolution(int resolution) {
      analogReadResolution(resolution);
    }
    inline int getResolution(void) {
      return analogReadResolutionVal();
    }

#ifdef  ADC_SINGLE_ENDED
    inline int read(ADC_TypeDef* ADCx, uint32_t ch, uint8_t differentialMode = ADC_SINGLE_ENDED) {
      return  analogReadChanel(ADCx, ch, differentialMode);
    }
#else
    inline int read(ADC_TypeDef* ADCx, uint32_t ch) {
      return analogReadChanel(ADCx, ch);
    }
#endif

#ifdef ADC_CHANNEL_VBAT
    inline int getVBAT(void) {   //VBAT unit: mVolt
#ifdef  ADC_CHANNEL_VBAT_DIV4  /*H7*/
//      int vref = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VREFINT, ADC_SINGLE_ENDED,16);
      return  getReference() * MAX_CONVERTED_VALUE / analogReadChanelAve(INTERNAL_Instance,  ADC_CHANNEL_VBAT_DIV4, ADC_SINGLE_ENDED,16) / ADC_VBAT_MULTI;
#elif defined(ADC_SINGLE_ENDED)
//      int vref = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VREFINT, ADC_SINGLE_ENDED,16);
      return  getReference() * MAX_CONVERTED_VALUE / analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VBAT, ADC_SINGLE_ENDED,16) / ADC_VBAT_MULTI;
#else
//	  int vref = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VREFINT,16);
      return  getReference() * MAX_CONVERTED_VALUE / analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VBAT,16) / ADC_VBAT_MULTI;
 //     return *VREFINT_CAL_ADDR * VREFINT_CAL_VREF/vref
#endif
    }
#endif

    inline int getReference(void) { // Vref+ unit: mVolt
#ifdef ADC_SINGLE_ENDED
      int date = analogReadChanelAve(INTERNAL_Instance,ADC_CHANNEL_VREFINT,ADC_SINGLE_ENDED,16);
#else
      int date = analogReadChanelAve(INTERNAL_Instance,ADC_CHANNEL_VREFINT,16);
#endif

#if defined(STM32F2)||defined(STM32F4)||defined(STM32F7) //defined(__LL_ADC_CALC_DATA_TO_VOLTAGE)  //F2/4
      return VDDA_APPLI * VREFINT / __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, date, LL_ADC_RESOLUTION_12B);  
#elif defined(__LL_ADC_CALC_VREFANALOG_VOLTAGE)       //F0/1/3/7 L0/1/4
       return  __LL_ADC_CALC_VREFANALOG_VOLTAGE(date, LL_ADC_RESOLUTION_12B); 
#else  //H7
      return 1225  * MAX_CONVERTED_VALUE / date ;
#endif
    }

    inline float temperatureCelsius(void) {
#ifdef ADC_SINGLE_ENDED
      int vref = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VREFINT, ADC_SINGLE_ENDED,32);
//      return (((analogReadChanel(INTERNAL_Instance, ADC_CHANNEL_TEMPSENSOR, ADC_SINGLE_ENDED) * 1225 / vref) - VSENS_AT_AMBIENT_TEMP) * 10.0 / AVG_SLOPE) + AMBIENT_TEMP;
      int date = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_TEMPSENSOR, ADC_SINGLE_ENDED,32);
#else
      int vref = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_VREFINT,32);
//	  float    vref = analogReadChanel(INTERNAL_Instance, ADC_CHANNEL_VREFINT)/ MAX_CONVERTED_VALUE * 3300;  	
      int date = analogReadChanelAve(INTERNAL_Instance, ADC_CHANNEL_TEMPSENSOR,32);
#endif

#ifdef __LL_ADC_CALC_TEMPERATURE
	  return __LL_ADC_CALC_TEMPERATURE(vref, 
                                       date,
                                       LL_ADC_RESOLUTION_12B);
#elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
      return __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(INTERNAL_TEMPSENSOR_AVGSLOPE, 
	                                              INTERNAL_TEMPSENSOR_V25,
                                                  INTERNAL_TEMPSENSOR_V25_TEMP,
                                                  getReference(),
                                                  date,
                                                  LL_ADC_RESOLUTION_12B);
#else  //H7
      return (((date * 1225.0 / vref) - VSENS_AT_AMBIENT_TEMP) * 10.0 / AVG_SLOPE) + AMBIENT_TEMP;
#endif	
    }

    inline float temperatureFahrenheit(void) {
      return (temperatureCelsius() * (9.0 / 5.0)) + 32.0;
    }
};
#pragma GCC diagnostic pop

extern ADCClass adc;

#endif  //__cplusplus

#endif  //__STM32ADC_H__
