#include "Arduino.h"

#ifndef _STM32DAC_H_
#define _STM32DAC_H_

#if defined(DAC)|| defined(DAC1)

#ifdef __cplusplus
extern "C" {
#endif

void DAC_Init(const uint32_t channel,const uint32_t trig);
void DAC_SetValue(uint32_t channel, uint16_t value);
uint16_t DAC_GetValue(uint32_t channel);
void DAC_Stop(uint32_t channel);
void DAC_Start(uint32_t channel);
void DAC_Start_DMA(uint32_t channel,uint32_t* pData, uint32_t Length, uint32_t Alignment);
void DAC_Stop_DMA(uint32_t channel);
void DACEx_TriangleWaveGenerate(uint32_t channel, uint32_t Amplitude,uint32_t dataHolding);
void DACEx_NoiseWaveGenerate(uint32_t channel, uint32_t Amplitude,uint32_t dataHolding);

#ifdef __cplusplus
}

template<const uint32_t channel>
class STM32DAC {
  public:

    STM32DAC() {}

    void Init(uint32_t trig = DAC_TRIGGER_NONE) {
      DAC_Init(channel,trig);
    }

    void write(uint16_t value) {
      DAC_SetValue(channel, value);
    }
	
    inline uint16_t read(void){
	  	return DAC_GetValue(channel);
	}

    void pause(void){
	  DAC_Stop(channel);
    }

	void triangleWaveGenerate(uint32_t Amplitude,uint32_t dataHolding = 0){
	  DACEx_TriangleWaveGenerate(channel, Amplitude,dataHolding);	
	}

	void noiseWaveGenerate(uint32_t Amplitude,uint32_t dataHolding = 0){
	  DACEx_NoiseWaveGenerate(channel, Amplitude,dataHolding);	
	}

    void resume(void){
	  DAC_Start(channel);
    }
	
    void startDMA(uint32_t* pData, uint32_t Length, uint32_t Alignment = DAC_ALIGN_12B_R){
		DAC_Start_DMA(channel,pData,Length,Alignment);
    }
	
    void stopDMA(void){
		DAC_Stop_DMA(channel);
    }
	
    STM32DAC &operator = (uint16_t value) {
      write(value);
      return *this;
    }

    operator uint16_t () { return read();}

    virtual ~STM32DAC() {}  // Do nothing
};

extern STM32DAC<DAC_CHANNEL_1>PA4_DACOUT;

#if defined(DAC_CHANNEL_2)
extern STM32DAC<DAC_CHANNEL_2>PA5_DACOUT;
#endif

#endif

#else
#error "This mcu does not support DAC!"
#endif

#endif /*_STM32DAC_H_*/
