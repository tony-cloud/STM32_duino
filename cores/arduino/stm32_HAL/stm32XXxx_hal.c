#include "stm32_build_defines.h"

// Ignore HAL errors when compiling with -Werror
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

#ifdef STM32F0
    #include "stm32f0xx_hal.c"
    #include "stm32f0xx_hal_adc.c"
    #include "stm32f0xx_hal_can.c"
    #include "stm32f0xx_hal_cec.c"
    #include "stm32f0xx_hal_comp.c"
    #include "stm32f0xx_hal_crc.c"
    #include "stm32f0xx_hal_dac.c"
    #include "stm32f0xx_hal_dma.c"
    #include "stm32f0xx_hal_flash.c"
    #include "stm32f0xx_hal_gpio.c"
    #include "stm32f0xx_hal_i2c.c"
    #include "stm32f0xx_hal_i2s.c"
    #include "stm32f0xx_hal_irda.c"
    #include "stm32f0xx_hal_iwdg.c"
    #include "stm32f0xx_hal_pcd.c"
    #include "stm32f0xx_hal_pwr.c"
    #include "stm32f0xx_hal_rcc.c"
    #include "stm32f0xx_hal_rtc.c"
//    #include "stm32f0xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f0xx_hal_smbus.c"
    #include "stm32f0xx_hal_spi.c"
    #include "stm32f0xx_hal_tim.c"
    #include "stm32f0xx_hal_tsc.c"
    #include "stm32f0xx_hal_uart.c"
    #include "stm32f0xx_hal_usart.c"
    #include "stm32f0xx_hal_wwdg.c"
    #include "stm32f0xx_ll_adc.c"
    #include "stm32f0xx_ll_comp.c"
    #include "stm32f0xx_ll_crc.c"
    #include "stm32f0xx_ll_crs.c"
    #include "stm32f0xx_ll_dac.c"
    #include "stm32f0xx_ll_dma.c"
    #include "stm32f0xx_ll_exti.c"
    #include "stm32f0xx_ll_gpio.c"
    #include "stm32f0xx_ll_i2c.c"
    #include "stm32f0xx_ll_pwr.c"
    #include "stm32f0xx_ll_rcc.c"
    #include "stm32f0xx_ll_rtc.c"
    #include "stm32f0xx_ll_spi.c"
    #include "stm32f0xx_ll_tim.c"
    #include "stm32f0xx_ll_usart.c"
    #include "stm32f0xx_ll_utils.c"
#endif
#ifdef STM32F1
    #include "stm32f1xx_hal.c"
    #include "stm32f1xx_hal_adc.c"
    #include "stm32f1xx_hal_can.c"
    #include "stm32f1xx_hal_cec.c"
    #include "stm32f1xx_hal_crc.c"
    #include "stm32f1xx_hal_dac.c"
    #include "stm32f1xx_hal_dma.c"
    #include "stm32f1xx_hal_eth.c"
    #include "stm32f1xx_hal_flash.c"
    #include "stm32f1xx_hal_gpio.c"
    #include "stm32f1xx_hal_hcd.c"
    #include "stm32f1xx_hal_i2c.c"
    #include "stm32f1xx_hal_i2s.c"
    #include "stm32f1xx_hal_irda.c"
    #include "stm32f1xx_hal_iwdg.c"
    #include "stm32f1xx_hal_mmc.c"
    #include "stm32f1xx_hal_nand.c"
    #include "stm32f1xx_hal_nor.c"
    #include "stm32f1xx_hal_pccard.c"
    #include "stm32f1xx_hal_pcd.c"
    #include "stm32f1xx_hal_pwr.c"
    #include "stm32f1xx_hal_rcc.c"
    #include "stm32f1xx_hal_rtc.c"
    #include "stm32f1xx_hal_sd.c"
//    #include "stm32f1xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f1xx_hal_spi.c"
    #include "stm32f1xx_hal_sram.c"
    #include "stm32f1xx_hal_tim.c"
    #include "stm32f1xx_hal_uart.c"
    #include "stm32f1xx_hal_usart.c"
    #include "stm32f1xx_hal_wwdg.c"
    #include "stm32f1xx_ll_adc.c"
    #include "stm32f1xx_ll_crc.c"
    #include "stm32f1xx_ll_dac.c"
    #include "stm32f1xx_ll_dma.c"
    #include "stm32f1xx_ll_exti.c"
    #include "stm32f1xx_ll_fsmc.c"
    #include "stm32f1xx_ll_gpio.c"
    #include "stm32f1xx_ll_i2c.c"
    #include "stm32f1xx_ll_pwr.c"
    #include "stm32f1xx_ll_rcc.c"
    #include "stm32f1xx_ll_rtc.c"
    #include "stm32f1xx_ll_sdmmc.c"
    #include "stm32f1xx_ll_spi.c"
    #include "stm32f1xx_ll_tim.c"
    #include "stm32f1xx_ll_usart.c"
    #include "stm32f1xx_ll_usb.c"
    #include "stm32f1xx_ll_utils.c"
#endif
#ifdef STM32F2
    #include "stm32f2xx_hal.c"
    #include "stm32f2xx_hal_adc.c"
    #include "stm32f2xx_hal_can.c"
    #include "stm32f2xx_hal_crc.c"
    #include "stm32f2xx_hal_cryp.c"
    #include "stm32f2xx_hal_dac.c"
    #include "stm32f2xx_hal_dcmi.c"
    #include "stm32f2xx_hal_dma.c"
    #include "stm32f2xx_hal_eth.c"
    #include "stm32f2xx_hal_flash.c"
    #include "stm32f2xx_hal_gpio.c"
    #include "stm32f2xx_hal_hash.c"
    #include "stm32f2xx_hal_hcd.c"
    #include "stm32f2xx_hal_i2c.c"
    #include "stm32f2xx_hal_i2s.c"
    #include "stm32f2xx_hal_irda.c"
    #include "stm32f2xx_hal_iwdg.c"
    #include "stm32f2xx_hal_nand.c"
    #include "stm32f2xx_hal_nor.c"
    #include "stm32f2xx_hal_pccard.c"
    #include "stm32f2xx_hal_pcd.c"
    #include "stm32f2xx_hal_pwr.c"
    #include "stm32f2xx_hal_rcc.c"
    #include "stm32f2xx_hal_rng.c"
    #include "stm32f2xx_hal_rtc.c"
    #include "stm32f2xx_hal_sd.c"
//    #include "stm32f2xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f2xx_hal_spi.c"
    #include "stm32f2xx_hal_sram.c"
    #include "stm32f2xx_hal_tim.c"
    #include "stm32f2xx_hal_uart.c"
    #include "stm32f2xx_hal_usart.c"
    #include "stm32f2xx_hal_wwdg.c"
    #include "stm32f2xx_ll_adc.c"
    #include "stm32f2xx_ll_crc.c"
    #include "stm32f2xx_ll_dac.c"
    #include "stm32f2xx_ll_dma.c"
    #include "stm32f2xx_ll_exti.c"
    #include "stm32f2xx_ll_fsmc.c"
    #include "stm32f2xx_ll_gpio.c"
    #include "stm32f2xx_ll_i2c.c"
    #include "stm32f2xx_ll_pwr.c"
    #include "stm32f2xx_ll_rcc.c"
    #include "stm32f2xx_ll_rng.c"
    #include "stm32f2xx_ll_rtc.c"
    #include "stm32f2xx_ll_sdmmc.c"
    #include "stm32f2xx_ll_spi.c"
    #include "stm32f2xx_ll_tim.c"
    #include "stm32f2xx_ll_usart.c"
    #include "stm32f2xx_ll_usb.c"
    #include "stm32f2xx_ll_utils.c"
#endif
#ifdef STM32F3
    #include "stm32f3xx_hal.c"
    #include "stm32f3xx_hal_adc.c"
    #include "stm32f3xx_hal_can.c"
    #include "stm32f3xx_hal_cec.c"
    #include "stm32f3xx_hal_comp.c"
    #include "stm32f3xx_hal_crc.c"
    #include "stm32f3xx_hal_dac.c"
    #include "stm32f3xx_hal_dma.c"
    #include "stm32f3xx_hal_flash.c"
    #include "stm32f3xx_hal_gpio.c"
    #include "stm32f3xx_hal_hrtim.c"
    #include "stm32f3xx_hal_i2c.c"
    #include "stm32f3xx_hal_i2s.c"
    #include "stm32f3xx_hal_irda.c"
    #include "stm32f3xx_hal_iwdg.c"
    #include "stm32f3xx_hal_nand.c"
    #include "stm32f3xx_hal_nor.c"
    #include "stm32f3xx_hal_opamp.c"
    #include "stm32f3xx_hal_pccard.c"
    #include "stm32f3xx_hal_pcd.c"
    #include "stm32f3xx_hal_pwr.c"
    #include "stm32f3xx_hal_rcc.c"
    #include "stm32f3xx_hal_rtc.c"
    #include "stm32f3xx_hal_sdadc.c"
//    #include "stm32f3xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f3xx_hal_smbus.c"
    #include "stm32f3xx_hal_spi.c"
    #include "stm32f3xx_hal_sram.c"
    #include "stm32f3xx_hal_tim.c"
    #include "stm32f3xx_hal_tsc.c"
    #include "stm32f3xx_hal_uart.c"
    #include "stm32f3xx_hal_usart.c"
    #include "stm32f3xx_hal_wwdg.c"
    #include "stm32f3xx_ll_adc.c"
    #include "stm32f3xx_ll_comp.c"
    #include "stm32f3xx_ll_crc.c"
    #include "stm32f3xx_ll_dac.c"
    #include "stm32f3xx_ll_dma.c"
    #include "stm32f3xx_ll_exti.c"
    #include "stm32f3xx_ll_fmc.c"
    #include "stm32f3xx_ll_gpio.c"
    #include "stm32f3xx_ll_hrtim.c"
    #include "stm32f3xx_ll_i2c.c"
    #include "stm32f3xx_ll_opamp.c"
    #include "stm32f3xx_ll_pwr.c"
    #include "stm32f3xx_ll_rcc.c"
    #include "stm32f3xx_ll_rtc.c"
    #include "stm32f3xx_ll_spi.c"
    #include "stm32f3xx_ll_tim.c"
    #include "stm32f3xx_ll_usart.c"
    #include "stm32f3xx_ll_utils.c"
#endif
#ifdef STM32F4
    #include "stm32f4xx_hal.c"
    #include "stm32f4xx_hal_adc.c"
    #include "stm32f4xx_hal_can.c"
    #include "stm32f4xx_hal_cec.c"
    #include "stm32f4xx_hal_crc.c"
    #include "stm32f4xx_hal_cryp.c"
    #include "stm32f4xx_hal_dac.c"
    #include "stm32f4xx_hal_dcmi.c"
    #include "stm32f4xx_hal_dfsdm.c"
    #include "stm32f4xx_hal_dma.c"
    #include "stm32f4xx_hal_dma2d.c"
    #include "stm32f4xx_hal_dsi.c"
    #include "stm32f4xx_hal_eth.c"
    #include "stm32f4xx_hal_flash.c"
    #include "stm32f4xx_hal_flash_ramfunc.c"
    #include "stm32f4xx_hal_fmpi2c.c"
    #include "stm32f4xx_hal_gpio.c"
    #include "stm32f4xx_hal_hash.c"
    #include "stm32f4xx_hal_hcd.c"
    #include "stm32f4xx_hal_i2c.c"
    #include "stm32f4xx_hal_i2s.c"
    #include "stm32f4xx_hal_irda.c"
    #include "stm32f4xx_hal_iwdg.c"
    #include "stm32f4xx_hal_lptim.c"
    #include "stm32f4xx_hal_ltdc.c"
    #include "stm32f4xx_hal_mmc.c"
    #include "stm32f4xx_hal_nand.c"
    #include "stm32f4xx_hal_nor.c"
    #include "stm32f4xx_hal_pccard.c"
    #include "stm32f4xx_hal_pcd.c"
    #include "stm32f4xx_hal_pwr.c"
    #include "stm32f4xx_hal_qspi.c"
    #include "stm32f4xx_hal_rcc.c"
    #include "stm32f4xx_hal_rng.c"
    #include "stm32f4xx_hal_rtc.c"
    #include "stm32f4xx_hal_sai.c"
    #include "stm32f4xx_hal_sd.c"
    #include "stm32f4xx_hal_sdram.c"
//    #include "stm32f4xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f4xx_hal_spdifrx.c"
    #include "stm32f4xx_hal_spi.c"
    #include "stm32f4xx_hal_sram.c"
    #include "stm32f4xx_hal_tim.c"
    #include "stm32f4xx_hal_uart.c"
    #include "stm32f4xx_hal_usart.c"
    #include "stm32f4xx_hal_wwdg.c"
    #include "stm32f4xx_ll_adc.c"
    #include "stm32f4xx_ll_crc.c"
    #include "stm32f4xx_ll_dac.c"
    #include "stm32f4xx_ll_dma.c"
    #include "stm32f4xx_ll_dma2d.c"
    #include "stm32f4xx_ll_exti.c"
    #include "stm32f4xx_ll_fmc.c"
    #include "stm32f4xx_ll_fsmc.c"
    #include "stm32f4xx_ll_gpio.c"
    #include "stm32f4xx_ll_i2c.c"
    #include "stm32f4xx_ll_lptim.c"
    #include "stm32f4xx_ll_pwr.c"
    #include "stm32f4xx_ll_rcc.c"
    #include "stm32f4xx_ll_rng.c"
    #include "stm32f4xx_ll_rtc.c"
    #include "stm32f4xx_ll_sdmmc.c"
    #include "stm32f4xx_ll_spi.c"
    #include "stm32f4xx_ll_tim.c"
    #include "stm32f4xx_ll_usart.c"
    #include "stm32f4xx_ll_usb.c"
    #include "stm32f4xx_ll_utils.c"
#endif
#ifdef STM32F7
    #include "stm32f7xx_hal.c"
    #include "stm32f7xx_hal_adc.c"
    #include "stm32f7xx_hal_can.c"
    #include "stm32f7xx_hal_cec.c"
    #include "stm32f7xx_hal_crc.c"
    #include "stm32f7xx_hal_cryp.c"
    #include "stm32f7xx_hal_dac.c"
    #include "stm32f7xx_hal_dcmi.c"
    #include "stm32f7xx_hal_dfsdm.c"
    #include "stm32f7xx_hal_dma.c"
    #include "stm32f7xx_hal_dma2d.c"
    #include "stm32f7xx_hal_dsi.c"
    #include "stm32f7xx_hal_eth.c"
    #include "stm32f7xx_hal_flash.c"
    #include "stm32f7xx_hal_gpio.c"
    #include "stm32f7xx_hal_hash.c"
    #include "stm32f7xx_hal_hcd.c"
    #include "stm32f7xx_hal_i2c.c"
    #include "stm32f7xx_hal_i2s.c"
    #include "stm32f7xx_hal_irda.c"
    #include "stm32f7xx_hal_iwdg.c"
    #include "stm32f7xx_hal_jpeg.c"
    #include "stm32f7xx_hal_lptim.c"
    #include "stm32f7xx_hal_ltdc.c"
    #include "stm32f7xx_hal_mdios.c"
    #include "stm32f7xx_hal_mmc.c"
    #include "stm32f7xx_hal_nand.c"
    #include "stm32f7xx_hal_nor.c"
    #include "stm32f7xx_hal_pcd.c"
    #include "stm32f7xx_hal_pwr.c"
    #include "stm32f7xx_hal_qspi.c"
    #include "stm32f7xx_hal_rcc.c"
    #include "stm32f7xx_hal_rng.c"
    #include "stm32f7xx_hal_rtc.c"
    #include "stm32f7xx_hal_sai.c"
    #include "stm32f7xx_hal_sd.c"
    #include "stm32f7xx_hal_sdram.c"
//    #include "stm32f7xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32f7xx_hal_smbus.c"
    #include "stm32f7xx_hal_spdifrx.c"
    #include "stm32f7xx_hal_spi.c"
    #include "stm32f7xx_hal_sram.c"
    #include "stm32f7xx_hal_tim.c"
    #include "stm32f7xx_hal_uart.c"
    #include "stm32f7xx_hal_usart.c"
    #include "stm32f7xx_hal_wwdg.c"
    #include "stm32f7xx_ll_adc.c"
    #include "stm32f7xx_ll_crc.c"
    #include "stm32f7xx_ll_dac.c"
    #include "stm32f7xx_ll_dma.c"
    #include "stm32f7xx_ll_dma2d.c"
    #include "stm32f7xx_ll_exti.c"
    #include "stm32f7xx_ll_fmc.c"
    #include "stm32f7xx_ll_gpio.c"
    #include "stm32f7xx_ll_i2c.c"
    #include "stm32f7xx_ll_lptim.c"
    #include "stm32f7xx_ll_pwr.c"
    #include "stm32f7xx_ll_rcc.c"
    #include "stm32f7xx_ll_rng.c"
    #include "stm32f7xx_ll_rtc.c"
    #include "stm32f7xx_ll_sdmmc.c"
    #include "stm32f7xx_ll_spi.c"
    #include "stm32f7xx_ll_tim.c"
    #include "stm32f7xx_ll_usart.c"
    #include "stm32f7xx_ll_usb.c"
    #include "stm32f7xx_ll_utils.c"
#endif
#ifdef STM32H7
    #include "stm32h7xx_hal.c"
    #include "stm32h7xx_hal_adc.c"
    #include "stm32h7xx_hal_cec.c"
    #include "stm32h7xx_hal_comp.c"
    #include "stm32h7xx_hal_cortex.c"
    #include "stm32h7xx_hal_crc.c"
    #include "stm32h7xx_hal_cryp.c"
    #include "stm32h7xx_hal_dac.c"
    #include "stm32h7xx_hal_dcmi.c"
    #include "stm32h7xx_hal_dfsdm.c"
    #include "stm32h7xx_hal_dma.c"
    #include "stm32h7xx_hal_dma2d.c"
    #include "stm32h7xx_hal_eth.c"
    #include "stm32h7xx_hal_fdcan.c"
    #include "stm32h7xx_hal_flash.c"
    #include "stm32h7xx_hal_gpio.c"
    #include "stm32h7xx_hal_hash.c"
    #include "stm32h7xx_hal_hcd.c"
    #include "stm32h7xx_hal_hrtim.c"
    #include "stm32h7xx_hal_hsem.c"
    #include "stm32h7xx_hal_i2c.c"
	#undef TIMING_CLEAR_MASK //remove warning
//	#undef MAX_NBYTE_SIZE	 //remove warning
    #include "stm32h7xx_hal_i2s.c"
    #include "stm32h7xx_hal_irda.c"
    #include "stm32h7xx_hal_iwdg.c"
    #include "stm32h7xx_hal_jpeg.c"
    #include "stm32h7xx_hal_lptim.c"
    #include "stm32h7xx_hal_ltdc.c"
    #include "stm32h7xx_hal_mdios.c"
    #include "stm32h7xx_hal_mdma.c"
    #include "stm32h7xx_hal_mmc.c"
    #include "stm32h7xx_hal_nand.c"
    #include "stm32h7xx_hal_nor.c"
    #include "stm32h7xx_hal_opamp.c"
    #include "stm32h7xx_hal_pcd.c"
    #include "stm32h7xx_hal_pwr.c"
    #include "stm32h7xx_hal_qspi.c"
    #include "stm32h7xx_hal_rcc.c"
    #include "stm32h7xx_hal_rng.c"
    #include "stm32h7xx_hal_rtc.c"
    #include "stm32h7xx_hal_sai.c"
    #include "stm32h7xx_hal_sd.c"
    #include "stm32h7xx_hal_sdram.c"
//    #include "stm32h7xx_hal_smartcard.c"
	#undef USART_CR3_FIELDS	 //remove warning
    #include "stm32h7xx_hal_smbus.c"
    #include "stm32h7xx_hal_spdifrx.c"
    #include "stm32h7xx_hal_spi.c"
    #include "stm32h7xx_hal_sram.c"
    #include "stm32h7xx_hal_swpmi.c"
    #include "stm32h7xx_hal_tim.c"
    #include "stm32h7xx_hal_uart.c"
	#undef USART_CR1_FIELDS	 //remove warning
	#undef USART_CR2_FIELDS	 //remove warning
	#undef USART_CR3_FIELDS	 //remove warning
	#undef USART_BRR_MAX     //remove warning
    #include "stm32h7xx_hal_usart.c"
    #include "stm32h7xx_hal_wwdg.c"
    #include "stm32h7xx_ll_delayblock.c"
    #include "stm32h7xx_ll_fmc.c"
    #include "stm32h7xx_ll_sdmmc.c"
    #include "stm32h7xx_ll_usb.c"
    #include "stm32h7xx_ll_adc.c"
    #include "stm32h7xx_ll_crc.c"
    #include "stm32h7xx_ll_dac.c"
    #include "stm32h7xx_ll_dma.c"
    #include "stm32h7xx_ll_dma2d.c"
    #include "stm32h7xx_ll_exti.c"
    #include "stm32h7xx_ll_gpio.c"
    #include "stm32h7xx_ll_i2c.c"
    #include "stm32h7xx_ll_lptim.c"
    #include "stm32h7xx_ll_pwr.c"
    #include "stm32h7xx_ll_rcc.c"
    #include "stm32h7xx_ll_rng.c"
    #include "stm32h7xx_ll_rtc.c"
    #include "stm32h7xx_ll_spi.c"
    #include "stm32h7xx_ll_tim.c"
    #include "stm32h7xx_ll_usart.c"
    #undef assert_param
    #define USE_FULL_LL_DRIVER   /*reomve warning*/
    #include "stm32h7xx_ll_utils.c"
#endif
#ifdef STM32L0
    #include "stm32l0xx_hal.c"
    #include "stm32l0xx_hal_adc.c"
    #include "stm32l0xx_hal_comp.c"
    #include "stm32l0xx_hal_crc.c"
    #include "stm32l0xx_hal_cryp.c"
    #include "stm32l0xx_hal_dac.c"
    #include "stm32l0xx_hal_dma.c"
    #include "stm32l0xx_hal_firewall.c"
    #include "stm32l0xx_hal_flash.c"
    #include "stm32l0xx_hal_flash_ramfunc.c"
    #include "stm32l0xx_hal_gpio.c"
    #include "stm32l0xx_hal_i2c.c"
    #include "stm32l0xx_hal_i2s.c"
    #include "stm32l0xx_hal_irda.c"
    #include "stm32l0xx_hal_iwdg.c"
    #include "stm32l0xx_hal_lcd.c"
    #include "stm32l0xx_hal_lptim.c"
    #include "stm32l0xx_hal_pcd.c"
    #include "stm32l0xx_hal_pwr.c"
    #include "stm32l0xx_hal_rcc.c"
    #include "stm32l0xx_hal_rng.c"
    #include "stm32l0xx_hal_rtc.c"
//    #include "stm32l0xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
	#undef TIMING_CLEAR_MASK	 //remove warning
    #include "stm32l0xx_hal_smbus.c"
    #include "stm32l0xx_hal_spi.c"
    #include "stm32l0xx_hal_tim.c"
    #include "stm32l0xx_hal_tsc.c"
    #include "stm32l0xx_hal_uart.c"
	#undef USART_CR1_FIELDS	 //remove warning
	#undef USART_BRR_MAX     //remove warning
    #include "stm32l0xx_hal_usart.c"
    #include "stm32l0xx_hal_wwdg.c"
    #include "stm32l0xx_ll_adc.c"
    #include "stm32l0xx_ll_comp.c"
    #include "stm32l0xx_ll_crc.c"
    #include "stm32l0xx_ll_crs.c"
    #include "stm32l0xx_ll_dac.c"
    #include "stm32l0xx_ll_dma.c"
    #include "stm32l0xx_ll_exti.c"
    #include "stm32l0xx_ll_gpio.c"
    #include "stm32l0xx_ll_i2c.c"
    #include "stm32l0xx_ll_lptim.c"
    #include "stm32l0xx_ll_lpuart.c"
    #include "stm32l0xx_ll_pwr.c"
    #include "stm32l0xx_ll_rcc.c"
    #include "stm32l0xx_ll_rng.c"
    #include "stm32l0xx_ll_rtc.c"
    #include "stm32l0xx_ll_spi.c"
    #include "stm32l0xx_ll_tim.c"
    #include "stm32l0xx_ll_usart.c"
    #include "stm32l0xx_ll_utils.c"
#endif
#ifdef STM32L1
    #include "stm32l1xx_hal.c"
    #include "stm32l1xx_hal_adc.c"
    #include "stm32l1xx_hal_comp.c"
    #include "stm32l1xx_hal_crc.c"
    #include "stm32l1xx_hal_cryp.c"
    #include "stm32l1xx_hal_dac.c"
    #include "stm32l1xx_hal_dma.c"
    #include "stm32l1xx_hal_flash.c"
    #include "stm32l1xx_hal_flash_ramfunc.c"
    #include "stm32l1xx_hal_gpio.c"
    #include "stm32l1xx_hal_i2c.c"
    #include "stm32l1xx_hal_i2s.c"
    #include "stm32l1xx_hal_irda.c"
    #include "stm32l1xx_hal_iwdg.c"
    #include "stm32l1xx_hal_lcd.c"
    #include "stm32l1xx_hal_nor.c"
    #include "stm32l1xx_hal_opamp.c"
    #include "stm32l1xx_hal_pcd.c"
    #include "stm32l1xx_hal_pwr.c"
    #include "stm32l1xx_hal_rcc.c"
    #include "stm32l1xx_hal_rtc.c"
    #include "stm32l1xx_hal_sd.c"
//    #include "stm32l1xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
    #include "stm32l1xx_hal_spi.c"
    #include "stm32l1xx_hal_sram.c"
    #include "stm32l1xx_hal_tim.c"
    #include "stm32l1xx_hal_uart.c"
    #include "stm32l1xx_hal_usart.c"
    #include "stm32l1xx_hal_wwdg.c"
    #include "stm32l1xx_ll_adc.c"
    #include "stm32l1xx_ll_comp.c"
    #include "stm32l1xx_ll_crc.c"
    #include "stm32l1xx_ll_dac.c"
    #include "stm32l1xx_ll_dma.c"
    #include "stm32l1xx_ll_exti.c"
    #include "stm32l1xx_ll_fsmc.c"
    #include "stm32l1xx_ll_gpio.c"
    #include "stm32l1xx_ll_i2c.c"
    #include "stm32l1xx_ll_opamp.c"
    #include "stm32l1xx_ll_pwr.c"
    #include "stm32l1xx_ll_rcc.c"
    #include "stm32l1xx_ll_rtc.c"
    #include "stm32l1xx_ll_sdmmc.c"
    #include "stm32l1xx_ll_spi.c"
    #include "stm32l1xx_ll_tim.c"
    #include "stm32l1xx_ll_usart.c"
    #include "stm32l1xx_ll_utils.c"
#endif
#ifdef STM32L4
    #include "stm32l4xx_hal.c"
    #include "stm32l4xx_hal_adc.c"
    #include "stm32l4xx_hal_can.c"
    #include "stm32l4xx_hal_comp.c"
    #include "stm32l4xx_hal_crc.c"
    #include "stm32l4xx_hal_cryp.c"
    #include "stm32l4xx_hal_dac.c"
    #include "stm32l4xx_hal_dcmi.c"
    #include "stm32l4xx_hal_dfsdm.c"
    #include "stm32l4xx_hal_dma.c"
    #include "stm32l4xx_hal_dma2d.c"
    #include "stm32l4xx_hal_firewall.c"
    #include "stm32l4xx_hal_flash.c"
    #include "stm32l4xx_hal_flash_ramfunc.c"
    #include "stm32l4xx_hal_gpio.c"
    #include "stm32l4xx_hal_hash.c"
    #include "stm32l4xx_hal_hcd.c"
    #include "stm32l4xx_hal_i2c.c"
    #include "stm32l4xx_hal_irda.c"
    #include "stm32l4xx_hal_iwdg.c"
    #include "stm32l4xx_hal_lcd.c"
    #include "stm32l4xx_hal_lptim.c"
    #include "stm32l4xx_hal_nand.c"
    #include "stm32l4xx_hal_nor.c"
    #include "stm32l4xx_hal_opamp.c"
    #include "stm32l4xx_hal_pcd.c"
    #include "stm32l4xx_hal_pwr.c"
    #include "stm32l4xx_hal_qspi.c"
    #include "stm32l4xx_hal_rcc.c"
    #include "stm32l4xx_hal_rng.c"
    #include "stm32l4xx_hal_rtc.c"
    #include "stm32l4xx_hal_sai.c"
    #include "stm32l4xx_hal_sd.c"
//    #include "stm32l4xx_hal_smartcard.c"  //move to stm32XXxx_hal_ex.c by huaweiwx@sina.com 2017.11.12
	#undef TIMING_CLEAR_MASK	 //remove warning
    #include "stm32l4xx_hal_smbus.c"
    #include "stm32l4xx_hal_spi.c"
    #include "stm32l4xx_hal_sram.c"
    #include "stm32l4xx_hal_swpmi.c"
    #include "stm32l4xx_hal_tim.c"
    #include "stm32l4xx_hal_tsc.c"
    #include "stm32l4xx_hal_uart.c"
    #undef USART_CR1_FIELDS  // remove warning "USART_CR1_FIELDS" redefined	        by huaweiwx@sina.com 2018.01.26
    #undef USART_CR3_FIELDS  // remove warning "USART_CR3_FIELDS" L4R5 redefined	by huaweiwx@sina.com 2018.02.27
	#undef USART_BRR_MAX     //remove warning
    #include "stm32l4xx_hal_usart.c"
    #include "stm32l4xx_hal_wwdg.c"
    #include "stm32l4xx_ll_adc.c"
    #include "stm32l4xx_ll_comp.c"
    #include "stm32l4xx_ll_crc.c"
    #include "stm32l4xx_ll_crs.c"
    #include "stm32l4xx_ll_dac.c"
    #include "stm32l4xx_ll_dma.c"
    #include "stm32l4xx_ll_dma2d.c"
    #include "stm32l4xx_ll_exti.c"
    #include "stm32l4xx_ll_fmc.c"
    #include "stm32l4xx_ll_gpio.c"
    #include "stm32l4xx_ll_i2c.c"
    #include "stm32l4xx_ll_lptim.c"
    #include "stm32l4xx_ll_lpuart.c"
    #include "stm32l4xx_ll_opamp.c"
    #include "stm32l4xx_ll_pwr.c"
    #include "stm32l4xx_ll_rcc.c"
    #include "stm32l4xx_ll_rng.c"
    #include "stm32l4xx_ll_rtc.c"
    #include "stm32l4xx_ll_sdmmc.c"
    #include "stm32l4xx_ll_spi.c"
    #include "stm32l4xx_ll_swpmi.c"
    #include "stm32l4xx_ll_tim.c"
    #include "stm32l4xx_ll_usart.c"
    #include "stm32l4xx_ll_usb.c"
    #include "stm32l4xx_ll_utils.c"
#endif
