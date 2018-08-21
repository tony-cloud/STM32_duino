/*
  Triangle/noise WaveGenerate demo

  PA4_DACOUT and PA5_DACOUT are predefined instances of class STM32DAC.

  huaweiwx@sina.com 2018.7.21
*/

#include "STM32DAC.h"
#include "HardwareBaseTimer.h"

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Triangle/noise wave generate demo...");

  /*
     @param  Amplitude Select max triangle amplitude.
          This parameter can be one of the following values:
                @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
                @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
                @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
                @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
                @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
                @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
                @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
                @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
                @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
                @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
                @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
                @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
  */
  Timer6.setPeriod(0); // calculate period: 1000000us/HZ/NUMS
  Timer6.resume(TIM_TRGO_UPDATE);

  PA4_DACOUT.Init(DAC_TRIGGER_T6_TRGO);
  PA4_DACOUT.triangleWaveGenerate(DAC_TRIANGLEAMPLITUDE_4095);
  //PA4_DACOUT.noiseWaveGenerate(DAC_TRIANGLEAMPLITUDE_4095);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalToggle(LED_BUILTIN);
  delay(500);
}

