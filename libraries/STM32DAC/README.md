# STM32DAC Lib
  Arduino library to support STM32 DAC.

## Class & instance

* **`STM32DAC<DAC_CHANNEL_x>`**: creat a instance.<br>
 **param** `DAC_CHANNEL_x` is `DAC_CHANNEL_1` or `DAC_CHANNEL_2`.<br>

* This lib had predefined two instances: `PA4_DACOUT` and `PA5_DACOUT`.

## API

* **`void Init(trig)`**: initialized the DAC.<br>
  **param** `trig` is `DAC_TRIGGER_NONE` `DAC_TRIGGER_T2_TRGO` `DAC_TRIGGER_T4_TRGO` `DAC_TRIGGER_T5_TRGO` `DAC_TRIGGER_T6_TRGO` `DAC_TRIGGER_T7_TRGO` `DAC_TRIGGER_T8_TRGO` `DAC_TRIGGER_EXT_IT9` or  `DAC_TRIGGER_SOFTWARE`.default is `DAC_TRIGGER_NONE`
* **`void write(uint16_t val)`**: DAC output val.
* **`uint16_t read(void)`**: read the last DAC output val.
* **`void pause(void)`**: pause the DAC output.
* **`void resume(void)`**: resume the DAC output.
* **`void triangleWaveGenerate(uint32_t Amplitude,uint32_t dataHolding = 0)`**:DAC triangle wave generate.<br>
* **`void noiseWaveGenerate(uint32_t Amplitude,uint32_t dataHolding = 0)`**:DAC noise wave generate.<br>