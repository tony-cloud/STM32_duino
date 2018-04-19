/**
 *  stm32generic
 *  interrupt, continuous conversion.
 *  Works OK
 * keep sample time >= 56 or interrupt processing takes all CPU cycles.
 * Convert time ~3.5 uS. could be much faster in one-shot mode, with shorter sample time.
  ******************************************************************************
  * @file    ADC/ADC_RegularConversion_Interrupt/Src/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    17-February-2017
  * @brief   This example describes how to use an Interrupt to convert 
  *          continuously data
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup ADC_RegularConversion_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ADC handler declaration */

/* Variable used to get converted value */
__IO uint16_t uhADCxConvertedValue = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void setup()
{
  HAL_Init();
  
#define TXPIN PC10  
#define RXPIN PC11
  SERIALX.setPins(TXPIN,RXPIN); 
  SERIALX.begin(15200);
  delay(200);
  SERIALX.println("ADC Demo - Single Channel Regular Conversion, Interrupts: ADC1 on PA1");
  
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);
  BSP_LED_Off(LED1);
  BSP_LED_Off(LED3);

  /*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle.Instance          = ADCx;
  
  AdcHandle.Init.ClockPrescaler         = ADC_CLOCKPRESCALER_PCLK_DIV2;
  AdcHandle.Init.Resolution             = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign              = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ScanConvMode           = DISABLE;
  AdcHandle.Init.EOCSelection           = DISABLE;
  AdcHandle.Init.ContinuousConvMode     = ENABLE;
  AdcHandle.Init.NbrOfConversion        = 1;
  AdcHandle.Init.DiscontinuousConvMode  = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion    = 0;
  AdcHandle.Init.ExternalTrigConvEdge   = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv       = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DMAContinuousRequests  = DISABLE;

  if(HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  SERIALX.println("Done HAL_ADC_Init");
  /*##-2- Configure ADC regular channel ######################################*/  
  sConfig.Channel = ADCx_CHANNEL;
  sConfig.Rank = 1;
  /************ NO SHORTER THAN 56 CYCLES OR ALL PROCESSING TIME IS USED BY INTERRUPT ROUTINE ***************/
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES; // SEE ABOVE!!!!
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler();
  }

  BSP_LED_Off(LED1);
  SERIALX.println("Starting conversions");
   
  /*##-3- Start the conversion process and enable interrupt ##################*/  
  if(HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)
  {
    /***** HAL_ADC_Start_IT() always returns HAL_OK ******/
    Error_Handler();
  }  
}

int loops = 0;
volatile uint32_t lastone, thisone; // timing variables
volatile int elapsed;
void loop()
{

  SERIALX.print(loops++);
  SERIALX.print(", Conv time ");
  SERIALX.print(elapsed);
  SERIALX.print(" us, Value = ");
  SERIALX.println(uhADCxConvertedValue);
  
  delay(200);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  SERIALX.println("Error!!!");
  
  /* Short pulses */
   while(1) { 
     BSP_LED_On(LED3);
     delay (100);
     BSP_LED_Off(LED3);
     delay (500);
    } 
}
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc){
 // do nothing for now
}
/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and 
  *         you can add your own implementation.    
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  /* time between interrupts
   *  
   */
  thisone = micros();
  elapsed = thisone - lastone;
  lastone = thisone;  
  
  /* Get the converted value of regular channel */ 
  uhADCxConvertedValue = HAL_ADC_GetValue(AdcHandle);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 

  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */


   SERIALX.print("Assert failed! ");
   SERIALX.print("File '");
   SERIALX.print((char*)file);
   SERIALX.print("', Line ");
   SERIALX.println(line);
  
  /* Rapid blink */
   while(1) { 
     BSP_LED_On(LED3);
     delay (100);
     BSP_LED_Off(LED3);
     delay (100);
    } 
}
#endif

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
