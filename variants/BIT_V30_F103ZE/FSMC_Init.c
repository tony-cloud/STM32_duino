#include "bsp.h"

#ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void _Error_Handler(char* file, uint32_t line);
static uint32_t FSMC_Initialized = 0;
void STM_FSMC_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  FSMC_NORSRAM_TimingTypeDef Timing;
  
  FSMC_NAND_PCC_TimingTypeDef ComSpaceTiming;
  FSMC_NAND_PCC_TimingTypeDef AttSpaceTiming;
  
  if (FSMC_Initialized) return;

  /* Peripheral clock enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_FSMC_CLK_ENABLE();
  
  
/** FSMC GPIO Configuration  
//data & addr
  PD14   ------> FSMC_D0
  PD15   ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10   ------> FSMC_D7
  PE11   ------> FSMC_D8
  PE12   ------> FSMC_D9
  PE13   ------> FSMC_D10
  PE14   ------> FSMC_D11
  PE15   ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10   ------> FSMC_D15
  PG0   ------> FSMC_A10  //RS
//ctrl
  PD4   ------> FSMC_NOE  //RD
  PD5   ------> FSMC_NWE  //WR
  PG12   ------> FSMC_NE4 //CS 
  */
  /* GPIO_InitStruct */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15 
                          |GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

//lcd FSMC
SRAM_HandleTypeDef fsmcLcdHandle;
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds)
{ 	
  FSMC_NORSRAM_TimingTypeDef rwTiming;

  STM_FSMC_GPIO_Init();
  /** Perform the SRAM4(LCD) initialization sequence
  */
  fsmcLcdHandle.Instance = FSMC_NORSRAM_DEVICE;
  fsmcLcdHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* fsmcLcdHandle.Init */
  fsmcLcdHandle.Init.NSBank = FSMC_NORSRAM_BANK4;
  fsmcLcdHandle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  fsmcLcdHandle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  fsmcLcdHandle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  fsmcLcdHandle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  fsmcLcdHandle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  fsmcLcdHandle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  fsmcLcdHandle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  fsmcLcdHandle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  fsmcLcdHandle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  fsmcLcdHandle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
//  fsmcLcdHandle.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  /* Timing */
  rwTiming.AddressSetupTime = _as/14;	//   1000/72(HCLK) =14ns
  rwTiming.AddressHoldTime =     1;
  rwTiming.DataSetupTime =    _ds/14;	//   1000/72(HCLK) =14ns
  rwTiming.BusTurnAroundDuration = 1;
  rwTiming.CLKDivision = 2;
  rwTiming.DataLatency = 2;
  rwTiming.AccessMode = FSMC_ACCESS_MODE_A;


 /* ExtTiming */

  if (HAL_SRAM_Init(&fsmcLcdHandle, &rwTiming, NULL) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}


#ifndef  LCD_ADDR_SETUPTIME
# define LCD_ADDR_SETUPTIME 20
#endif
#ifndef  LCD_DATA_SETUPTIME
# define LCD_DATA_SETUPTIME 45
#endif

void STM_FSMC_LCD_Init(void)
{
	STM_FSMC_LCD_TimeSet(LCD_ADDR_SETUPTIME, LCD_DATA_SETUPTIME);
#ifdef LCDBL_PIN
    pinMode(LCDBL_PIN,OUTPUT);
# ifdef LCDBL_ON
	digitalWrite(LCDBL_PIN, LCDBL_ON); //backlight on if can set
# else	
	digitalWrite(LCDBL_PIN, HIGH); //backlight on if can set
# endif	
#endif	
}

