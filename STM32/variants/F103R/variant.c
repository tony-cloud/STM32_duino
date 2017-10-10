#include "stm32_build_defines.h"
#include "stm32_def.h"
//      2016.9.18 huawei <huaweiwx@sina.com>
//HSI
#ifdef USE_HSI
	   #define BOARD_RCC_PLLMUL RCC_PLL_MUL12
       #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV1_5
#else
#  if OSC == 12
     #if F_CPU == 120000000
       #define BOARD_RCC_PLLMUL RCC_PLL_MUL10
	   #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV2_5
	 #elif F_CPU == 96000000
	   #define BOARD_RCC_PLLMUL RCC_PLL_MUL8
	   #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV2
	 #else
	   #define BOARD_RCC_PLLMUL RCC_PLL_MUL6
	   #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV1_5
     #endif
#  else
     #if F_CPU == 120000000
       #define BOARD_RCC_PLLMUL RCC_PLL_MUL15
       #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV2_5	   
	 #elif F_CPU == 96000000
	   #define BOARD_RCC_PLLMUL RCC_PLL_MUL12
       #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV2
	 #else
	   #define BOARD_RCC_PLLMUL RCC_PLL_MUL9
       #define BOARD_USB_PLLDIV RCC_USBCLKSOURCE_PLL_DIV1_5
     #endif
#  endif
#endif

extern void Error_Handler(void);  
#if defined(USE_HSI)
void void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = BOARD_RCC_PLLMUL;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = BOARD_USB_PLLDIV;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}
#else
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = BOARD_RCC_PLLMUL;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB; 
    PeriphClkInit.UsbClockSelection = BOARD_USB_PLLDIV; 
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
#if __has_include("FreeRTOS.h")  //huawei (huaweiwx@sina.com)
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);  
#else  
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif  
}
#endif